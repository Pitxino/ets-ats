/*
    Autor: Pitxino
    Plugin de telemetr�a para ETS2/ATS
    Versi�n optimizada para tipos nativos
*/

// Definiciones para indicar la versi�n m�nima de Windows a utilizar
#define WINVER 0x0500
#define _WIN32_WINNT 0x0500

// Inclusi�n de cabeceras del sistema y librer�as est�ndar
#include <windows.h> //Proporciona las definiciones, macros, funciones y estructuras necesarias para interactuar con el API de Windows. Es fundamental para realizar operaciones propias del sistema operativo (como obtener el directorio actual, trabajar con tiempos, gestionar ventanas, entre otros).
#include <stdio.h>  //Es la biblioteca est�ndar de entrada y salida en C. Incluye funciones para operaciones de lectura y escritura, como printf, scanf, fopen, entre otras, lo que permite trabajar con archivos, la consola y otros dispositivos de E/S.
#include <stdlib.h> //Contiene funciones para la gesti�n de memoria, conversi�n de datos, generaci�n de n�meros aleatorios, control de procesos, y otras utilidades generales. Por ejemplo, malloc, free, atoi, rand, etc.
#include <assert.h> //Proporciona la macro assert() que se utiliza para realizar comprobaciones en tiempo de ejecuci�n durante el desarrollo. Si la condici�n evaluada por assert() es falsa, el programa se detiene y se muestra un mensaje de error. Es muy �til para detectar errores durante la fase de depuraci�n.
#include <stdarg.h> //Permite definir funciones que aceptan un n�mero variable de argumentos (por ejemplo, funciones similares a printf). Incluye macros como va_start, va_arg y va_end para acceder a esos argumentos de forma segura.  
#include <sstream>  //Es parte de la biblioteca est�ndar de C++ y proporciona clases para manejar flujos de datos en forma de cadenas (string streams). Con std::stringstream, puedes construir, formatear y extraer datos de una cadena de texto de manera similar a como se trabaja con flujos de E/S tradicionales.
#include <iomanip>  // Para formatear los mensajes de log
#include <string>   // Para usar std::string

// Inclusi�n de las cabeceras de la SDK de telemetr�a de SCS y la espec�fica de Eurotrucks2
#include <scssdk_telemetry.h>
#include <eurotrucks2/scssdk_telemetry_eut2.h>

// Inclusi�n de archivos propios para manejo de puerto serial y opciones de configuraci�n
#include "serial.hpp"
#include "options.hpp"


// Variable global para el log del juego (se obtiene de la SDK)
scs_log_t game_log = NULL;

// Objeto Serial para el puerto COM
Serial serial_port;

// Variable para controlar la tasa de actualizaci�n (evitar env�os muy frecuentes)
unsigned long last_update = 0;

// Tama�o m�ximo del paquete a enviar y definiciones del encabezado del paquete
#define PACKET_MAX_SIZE 720
#define PACKET_SYNC 0xFF
#define PACKET_VER  2

// Buffer global para armar el paquete a enviar
unsigned char packet[PACKET_MAX_SIZE];

// Macro para empaquetar 8 valores booleanos en un �nico byte (cada bit representa un valor)
#define PACKBOOL(A,B,C,D,E,F,G,H) \
  (((unsigned char)(A) << 7) | ((unsigned char)(B) << 6) | \
   ((unsigned char)(C) << 5) | ((unsigned char)(D) << 4) | \
   ((unsigned char)(E) << 3) | ((unsigned char)(F) << 2) | \
   ((unsigned char)(G) << 1) | ((unsigned char)(H)))

// Estructura para almacenar todos los datos de telemetr�a recibidos del juego
struct telemetry_state_t
{
    float speed;                        // Velocidad (en m/s, se convierte a km/h en el plugin)
    float engine_rpm;                   // RPM del motor
    int engine_gear;                    // Marcha actual
    bool parking_brake;                 // Freno de estacionamiento
    bool motor_brake;                   // Freno motor
    float brake_air_pressure;           // Presi�n de aire en frenos
    bool brake_air_pressure_warning;    // Advertencia de presi�n de aire en frenos
    bool brake_air_pressure_emergency;  // Emergencia por presi�n de aire en frenos
    float brake_temperature;            // Temperatura de los frenos
    float fuel;                         // Cantidad de combustible
    bool fuel_warning;                  // Advertencia de combustible
    float fuel_average_consumption;     // Consumo promedio de combustible
    float fuel_capacity;                // Capacidad total del dep�sito de combustible
    float oil_pressure;                 // Presi�n del aceite
    bool oil_pressure_warning;          // Advertencia de presi�n de aceite
    float oil_temperature;              // Temperatura del aceite
    float water_temperature;            // Temperatura del agua
    bool water_temperature_warning;     // Advertencia de temperatura del agua
    float battery_voltage;              // Voltaje de la bater�a
    bool battery_voltage_warning;       // Advertencia de voltaje de la bater�a
    bool electric_enabled;              // Indica si est� activado el modo el�ctrico
    bool engine_enabled;                // Indica si el motor est� encendido
    bool light_lblinker;                // Intermitente izquierdo
    bool light_rblinker;                // Intermitente derecho
    bool light_parking;                 // Luz de estacionamiento
    bool light_low_beam;                // Luz baja
    bool light_high_beam;               // Luz alta
    bool light_brake;                   // Luz de freno
    bool light_reverse;                 // Luz de retroceso
    float odometer;                     // Od�metro (kil�metros recorridos)
    float cruise_control;               // Control de crucero
    bool light_beacon;                  // Luz de baliza
    float adblue;                       // Cantidad de AdBlue
    bool adblue_warning;                // Advertencia de AdBlue
    float adblue_average_consumption;   // Consumo promedio de AdBlue
    float adblue_capacity;              // Capacidad total del dep�sito de AdBlue
    bool wipers;                        // Estado de los limpiaparabrisas
    bool dashboard_backlight;           // Luz de fondo del tablero
    bool lift_axle_indicator;           // Indicador de eje levantado
    bool trailer_lift_axle_indicator;   // Indicador de eje levantado del remolque
    bool differential_lock;             // Bloqueo del diferencial
    bool hazard_warning;                // Advertencia de peligro (luces de emergencia)
} telemetry;

// Objeto para leer las opciones de configuraci�n (archivo de opciones)
Options option_file;

// Funci�n para enviar un paquete vac�o (se utiliza al iniciar o apagar el plugin)
void send_empty_packet()
{
    // Rellenar el paquete con ceros
    memset(packet, 0, PACKET_MAX_SIZE);
    // Establecer los primeros dos bytes: sincronizaci�n y versi�n
    packet[0] = PACKET_SYNC;
    packet[1] = PACKET_VER;
    // Enviar el paquete (solo se env�an 2 bytes)
    serial_port.write(packet, 2);
}

// Funci�n callback que se ejecuta al finalizar cada frame del juego
SCSAPI_VOID telemetry_frame_end(const scs_event_t, const void*, const scs_context_t)
{
    // Si el puerto serial no es v�lido, no se hace nada
    if (!serial_port.is_valid()) return;

    // Se utiliza GetTickCount() para obtener el tiempo actual en ms
    const unsigned long now = GetTickCount();
    // Si no han pasado al menos 50 ms desde el �ltimo env�o, se sale (para evitar saturaci�n)
    if (now - last_update < 50) return;
    last_update = now;

    // Se limpia el paquete
    memset(packet, 0, PACKET_MAX_SIZE);
    unsigned idx = 0;

    // Agregar encabezado: primer byte de sincronizaci�n y la versi�n
    packet[idx++] = PACKET_SYNC;
    packet[idx++] = PACKET_VER;

    // =============================================
    // === Secci�n de floats ===
    // Se convierten y copian los valores de telemetr�a al paquete
    // Se realiza una conversi�n cuando es necesario (por ejemplo, la velocidad se convierte a km/h)

    // Convertir velocidad de m/s a km/h y copiar
    float speed_kmh = fabs(telemetry.speed) * 3.6f;
    memcpy(&packet[idx], &speed_kmh, sizeof(float)); idx += sizeof(float);

    // Copiar RPM del motor
    float engine_rpm = telemetry.engine_rpm;
    memcpy(&packet[idx], &engine_rpm, sizeof(float)); idx += sizeof(float);

    // Copiar presi�n de aire en frenos
    float brake_air_pressure = telemetry.brake_air_pressure;
    memcpy(&packet[idx], &brake_air_pressure, sizeof(float)); idx += sizeof(float);

    // Copiar temperatura de los frenos
    float brake_temp = telemetry.brake_temperature;
    memcpy(&packet[idx], &brake_temp, sizeof(float)); idx += sizeof(float);

    // Calcular y copiar la relaci�n de combustible (proporci�n del tanque lleno)
    float fuel_ratio = telemetry.fuel / telemetry.fuel_capacity;
    memcpy(&packet[idx], &fuel_ratio, sizeof(float)); idx += sizeof(float);

    // Copiar presi�n del aceite
    float oil_pressure = telemetry.oil_pressure;
    memcpy(&packet[idx], &oil_pressure, sizeof(float)); idx += sizeof(float);

    // Copiar temperatura del aceite
    float oil_temp = telemetry.oil_temperature;
    memcpy(&packet[idx], &oil_temp, sizeof(float)); idx += sizeof(float);

    // Copiar temperatura del agua
    float water_temp = telemetry.water_temperature;
    memcpy(&packet[idx], &water_temp, sizeof(float)); idx += sizeof(float);

    // Copiar voltaje de la bater�a
    float battery_volt = telemetry.battery_voltage;
    memcpy(&packet[idx], &battery_volt, sizeof(float)); idx += sizeof(float);

    // Copiar valor de control de crucero
    float cruise_control = telemetry.cruise_control;
    memcpy(&packet[idx], &cruise_control, sizeof(float)); idx += sizeof(float);

    // Calcular y copiar la relaci�n de AdBlue (proporci�n del dep�sito lleno)
    float adblue_ratio = telemetry.adblue / telemetry.adblue_capacity;
    memcpy(&packet[idx], &adblue_ratio, sizeof(float)); idx += sizeof(float);

    // NUEVO: enviar el od�metro como float
    float odometer_val = telemetry.odometer;
    memcpy(&packet[idx], &odometer_val, sizeof(float)); idx += sizeof(float);


    // =============================================
    // === Nuevo Log Detallado ===
    // Se genera un log detallado que se env�a al juego cada segundo (1000 ms)
    static unsigned long last_log = 0;
    if (now - last_log > 1000) {
        std::stringstream log_stream;
        log_stream << "\n[Datos Telemetria]\n"
            << std::fixed << std::setprecision(1)
            << "speed_kmh: " << speed_kmh << " km/h\n"
            << "engine_rpm: " << engine_rpm << " RPM\n"
            << "brake_air_pressure: " << brake_air_pressure << " PSI\n"
            << "brake_temperature: " << brake_temp << " C\n"
            << "fuel_ratio: " << (fuel_ratio * 100.0f) << "%\n"
            << "oil_pressure: " << oil_pressure << " PSI\n"
            << "oil_temperature: " << oil_temp << " C\n"
            << "water_temperature: " << water_temp << " C\n"
            << "battery_voltage: " << battery_volt << " V\n"
            << "cruise_control: " << cruise_control << "\n"
            << "adblue_ratio: " << (adblue_ratio * 100.0f) << "%\n"
            << "\nLuces:\n"
            << "Beacon=" << telemetry.light_beacon << " "
            << "Parking=" << telemetry.parking_brake << " "
            << "L_Blinker=" << telemetry.light_lblinker << " "
            << "R_Blinker=" << telemetry.light_rblinker << "\n"
            << "Low_beam=" << telemetry.light_low_beam << " "
            << "High_beam=" << telemetry.light_high_beam << " "
            << "Brake_light=" << telemetry.light_brake << " "
            << "Reverse=" << telemetry.light_reverse << "\n"
            << "\nAlertas:\n"
            << "Fuel_warn=" << telemetry.fuel_warning << " "
            << "Battery_warn=" << telemetry.battery_voltage_warning << " "
            << "Oil_warn=" << telemetry.oil_pressure_warning << " "
            << "Water_warn=" << telemetry.water_temperature_warning << "\n"
            << "\nEstado:\n"
            << "Electric=" << telemetry.electric_enabled << " "
            << "Engine=" << telemetry.engine_enabled << " "
            << "Adblue_warn=" << telemetry.adblue_warning << "\n"
            << "\nOdometer: ";

        // Se agrega el valor del od�metro al log
        float odo = telemetry.odometer;
        log_stream << std::fixed << std::setprecision(0) << odo << " km";

        // Se env�a el log a trav�s de la funci�n game_log (de la SDK)
        game_log(SCS_LOG_TYPE_message, log_stream.str().c_str());
        last_log = now;
    }
    // === FIN: Nuevo c�digo de logging ===

    // === INICIO: Secci�n original de booleanos ===
    // Se empaquetan 8 valores booleanos en un solo byte usando la macro PACKBOOL.
    packet[idx++] = PACKBOOL(
        telemetry.light_beacon,
        telemetry.light_parking,
        telemetry.light_lblinker,
        telemetry.light_rblinker,
        telemetry.light_low_beam,
        telemetry.light_high_beam,
        telemetry.light_brake,
        telemetry.light_reverse
    );

    // Segundo byte de booleanos: otros indicadores y advertencias.
    packet[idx++] = PACKBOOL(
        telemetry.parking_brake,
        telemetry.motor_brake,
        telemetry.brake_air_pressure_warning,
        telemetry.brake_air_pressure_emergency,
        telemetry.fuel_warning,
        telemetry.battery_voltage_warning,
        telemetry.oil_pressure_warning,
        telemetry.water_temperature_warning
    );

    // Tercer byte de booleanos: indicadores adicionales.
    packet[idx++] = PACKBOOL(
        telemetry.differential_lock,
        telemetry.trailer_lift_axle_indicator,
        telemetry.lift_axle_indicator,
        telemetry.dashboard_backlight,
        telemetry.wipers,
        telemetry.adblue_warning,
        telemetry.electric_enabled,
        telemetry.engine_enabled
    );

    // Cuarto byte: solo se utiliza el �ltimo bit para hazard_warning.
    packet[idx++] = PACKBOOL(
        0, 0, 0, 0, 0, 0, 0,
        telemetry.hazard_warning
    );
    // === FIN: Secci�n original de booleanos ===

    // Se env�a el paquete completo a trav�s del puerto serial.
    serial_port.write(packet, idx);
}

// Funciones para almacenar valores recibidos (callbacks) en la estructura de telemetr�a
SCSAPI_VOID telemetry_store_float(const scs_string_t /*name*/, const scs_u32_t /*index*/,
    const scs_value_t* const value, const scs_context_t context)
{
    assert(value);
    assert(value->type == SCS_VALUE_TYPE_float);
    assert(context);
    *static_cast<float*>(context) = value->value_float.value;
}

SCSAPI_VOID telemetry_store_bool(const scs_string_t /*name*/, const scs_u32_t /*index*/,
    const scs_value_t* const value, const scs_context_t context)
{
    assert(value);
    assert(value->type == SCS_VALUE_TYPE_bool);
    assert(context);
    *static_cast<bool*>(context) = (value->value_bool.value != 0);
}

SCSAPI_VOID telemetry_store_s32(const scs_string_t /*name*/, const scs_u32_t /*index*/,
    const scs_value_t* const value, const scs_context_t context)
{
    assert(value);
    assert(value->type == SCS_VALUE_TYPE_s32);
    assert(context);
    *static_cast<int*>(context) = value->value_s32.value;
}

// Funci�n para recibir la configuraci�n del juego
SCSAPI_VOID telemetry_configuration(const scs_event_t /*event*/,
    const void* const event_info, const scs_context_t /*context*/)
{
    const struct scs_telemetry_configuration_t* const info =
        static_cast<const scs_telemetry_configuration_t*>(event_info);

    for (const scs_named_value_t* current = info->attributes; current->name; ++current)
    {
        // Macro para obtener la configuraci�n y almacenarla en la estructura de telemetr�a
#define GET_CONFIG(PROPERTY, TYPE) \
  if (strcmp(SCS_TELEMETRY_CONFIG_ATTRIBUTE_ ## PROPERTY, current->name) == 0) \
  { telemetry.PROPERTY = current->value.value_ ## TYPE.value; }

        GET_CONFIG(fuel_capacity, float);
        GET_CONFIG(adblue_capacity, float);
    }
}

// Funci�n para obtener el directorio actual de trabajo
void get_cwd(std::string& str)
{
    char buffer[256];
    GetCurrentDirectory(256, buffer);
    str.assign(buffer);
}

// Funci�n de inicializaci�n del plugin
SCSAPI_RESULT scs_telemetry_init(const scs_u32_t version,
    const scs_telemetry_init_params_t* const params)
{
    // Se verifica que la versi�n sea la soportada
    if (version != SCS_TELEMETRY_VERSION_1_00) {
        return SCS_RESULT_unsupported;
    }

    const scs_telemetry_init_params_v100_t* const version_params =
        static_cast<const scs_telemetry_init_params_v100_t*>(params);
    game_log = version_params->common.log;

    // Log inicializaci�n
    game_log(SCS_LOG_TYPE_message, "Plugin initialising");

    // Obtener el directorio de trabajo actual
    std::string cwd;
    get_cwd(cwd);
    game_log(SCS_LOG_TYPE_message, (std::string("Plugin CWD: ") + cwd).c_str());

    // Leer el archivo de opciones (configuraci�n)
    std::string option_filepath(cwd + "\\plugins\\dash_plugin.txt");
    if (!option_file.read_file(option_filepath))
    {
        game_log(SCS_LOG_TYPE_error,
            (std::string("Error reading settings file: ") + option_filepath).c_str());
        return SCS_RESULT_generic_error;
    }

    // Obtener el puerto COM de las opciones (por defecto "COM5")
    const std::string com_port = option_file.get_option_string("comport", "COM5");
    game_log(SCS_LOG_TYPE_message, (std::string("Using serial port: ") + com_port).c_str());

    // Abrir el puerto COM
    std::string errmsg;
    if (!serial_port.open(com_port, errmsg))
    {
        game_log(SCS_LOG_TYPE_error, errmsg.c_str());
        return SCS_RESULT_generic_error;
    }

    // Enviar un paquete vac�o al iniciar
    send_empty_packet();

    // Registrar los callbacks para eventos en el juego:
    // - telemetry_frame_end se llama al final de cada frame.
    // - telemetry_configuration se llama para recibir la configuraci�n.
    bool registered =
        (version_params->register_for_event(
            SCS_TELEMETRY_EVENT_frame_end, telemetry_frame_end, NULL) == SCS_RESULT_ok) &&
        (version_params->register_for_event(
            SCS_TELEMETRY_EVENT_configuration, telemetry_configuration, NULL) == SCS_RESULT_ok);

    // Registrar los canales de datos (variables de telemetr�a) para el cami�n.
#define REG_CHAN(CHANNEL, TYPE) \
  registered &= (version_params->register_for_channel( \
      SCS_TELEMETRY_TRUCK_CHANNEL_ ## CHANNEL, SCS_U32_NIL, SCS_VALUE_TYPE_ ## TYPE, \
      SCS_TELEMETRY_CHANNEL_FLAG_none, telemetry_store_ ## TYPE, &telemetry.CHANNEL) == SCS_RESULT_ok)

    REG_CHAN(speed, float);
    REG_CHAN(engine_rpm, float);
    REG_CHAN(engine_gear, s32);
    REG_CHAN(parking_brake, bool);
    REG_CHAN(motor_brake, bool);
    REG_CHAN(brake_air_pressure, float);
    REG_CHAN(brake_air_pressure_warning, bool);
    REG_CHAN(brake_air_pressure_emergency, bool);
    REG_CHAN(brake_temperature, float);
    REG_CHAN(fuel, float);
    REG_CHAN(fuel_warning, bool);
    REG_CHAN(fuel_average_consumption, float);

    REG_CHAN(oil_pressure, float);
    REG_CHAN(oil_pressure_warning, bool);
    REG_CHAN(oil_temperature, float);
    REG_CHAN(water_temperature, float);
    REG_CHAN(water_temperature_warning, bool);
    REG_CHAN(battery_voltage, float);
    REG_CHAN(battery_voltage_warning, bool);
    REG_CHAN(electric_enabled, bool);
    REG_CHAN(engine_enabled, bool);
    REG_CHAN(light_lblinker, bool);
    REG_CHAN(light_rblinker, bool);
    REG_CHAN(light_parking, bool);
    REG_CHAN(light_low_beam, bool);
    REG_CHAN(light_high_beam, bool);
    REG_CHAN(light_brake, bool);
    REG_CHAN(light_reverse, bool);
    REG_CHAN(odometer, float);
    REG_CHAN(cruise_control, float); // a�adido
    REG_CHAN(light_beacon, bool);
    REG_CHAN(adblue, float);
    //  REG_CHAN(adblue_average_consumption, float);

    REG_CHAN(adblue_warning, bool);
    REG_CHAN(wipers, bool);
    //  REG_CHAN(dashboard_backlight, float);
    REG_CHAN(lift_axle_indicator, bool);
    REG_CHAN(trailer_lift_axle_indicator, bool);
    REG_CHAN(differential_lock, bool);
    REG_CHAN(hazard_warning, bool);

    // Verificar que todos los callbacks se hayan registrado correctamente
    if (!registered)
    {
        game_log(SCS_LOG_TYPE_error, "Unable to register callbacks");
        return SCS_RESULT_generic_error;
    }

    // Inicializar la estructura de telemetr�a a cero
    memset(&telemetry, 0, sizeof(telemetry));

    return SCS_RESULT_ok;
}

// Funci�n de apagado del plugin
SCSAPI_VOID scs_telemetry_shutdown(void)
{
    send_empty_packet();   // Enviar paquete vac�o al apagar
    serial_port.close();   // Cerrar el puerto serial

    game_log(SCS_LOG_TYPE_message, "Plugin shutdown");
    game_log = NULL;
}

// Funci�n DllMain: se llama cuando el DLL se carga o descarga
BOOL APIENTRY DllMain(HMODULE /*module*/, DWORD reason_for_call, LPVOID /*reseved*/)
{
    if (reason_for_call == DLL_PROCESS_DETACH)
    {
        serial_port.close();  // Asegurarse de cerrar el puerto serial al descargar el DLL
    }
    return TRUE;
}

