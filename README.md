# TASA – Proyecto CO2

Monitor de CO2 con un ESP8266 (NodeMCU), un sensor **MH-Z19B** leído por PWM y un módulo **RAK3172** que envía las lecturas por LoRaWAN cada 60 segundos.

## Archivos

| Archivo | Descripción |
|---|---|
| `Prueba_co2.ino` | Prueba del sensor MH-Z19B. Lee el pulso PWM, calcula ppm con la fórmula del datasheet y lo imprime por serial. Incluye función de calibración manual de cero. |
| `RAK_TEST` | Puente serial para el RAK3172. Permite escribir comandos AT desde el monitor serial y ver la respuesta del módulo. |
| `Código integrado` | Firmware final. Configura el RAK3172 en modo LoRaWAN (OTAA, banda AU915, clase A), se une a la red y envía el CO2 como payload hexadecimal de 2 bytes. Escribir `cal` en el monitor serial dispara la calibración. |

## Conexiones

| Dispositivo | Pin del módulo | Pin del ESP8266 |
|---|---|---|
| MH-Z19B | PWM | D2 (GPIO4) |
| MH-Z19B | HD (calibración) | D1 |
| RAK3172 | TX | D7 (GPIO13) |
| RAK3172 | RX | D4 (GPIO2) |

Monitor serial y comunicación con el RAK3172 a 115200 baudios.

## Uso

1. Abrir el sketch en Arduino IDE con la placa NodeMCU 1.0 (ESP8266) seleccionada.
2. Ajustar `RANGE_PPM` (2000 o 5000) según la versión del sensor.
3. Reemplazar `DEVEUI`, `APPEUI` y `APPKEY` por los del dispositivo registrado en el servidor LoRaWAN.
4. Cargar el firmware y abrir el monitor serial.

## Payload

El valor de CO2 en ppm se envía como entero en 2 bytes hexadecimales por el puerto 2. Ejemplo: `041A` equivale a 1050 ppm.

## Notas

- Calibrar el cero solo en aire exterior estable (~400 ppm) tras 20 minutos de funcionamiento.
- Las credenciales LoRaWAN están escritas en el código; conviene cambiarlas si el repositorio es público.
