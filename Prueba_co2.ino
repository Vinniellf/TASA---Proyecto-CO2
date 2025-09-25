// Ejemplo para NodeMCU/ESP8266
// Conexiones:
// MH-Z19B PWM -> D2
// MH-Z19B HD  -> D1  (lo manejamos desde el ESP para la calibración manual)

const int PWM_PIN = 4;    // lectura PWM
const int HD_PIN  = D1;    // pin para activar calibración (LOW = calibrar)
const int RANGE_PPM = 2000; // pon 2000 o 5000 según tu sensor

void setup() {
  Serial.begin(115200);
  pinMode(PWM_PIN, INPUT);
  pinMode(HD_PIN, OUTPUT);
  digitalWrite(HD_PIN, HIGH); // mantener inactivo (no GND)
  Serial.println("MH-Z19B PWM reader - inicio");
  delay(2000); // espera del sistema
}

// Llamar manualZeroCalibrate() cuando quieras (desconecta antes si no estás afuera)
void manualZeroCalibrate() {
  Serial.println(">>> Calibrando cero: asegúrate de estar en aire exterior (~400 ppm) y estable 20+ minutos");
  digitalWrite(HD_PIN, LOW);  // baja el pin HD a GND
  delay(8000);                // >=7 segundos (recomendado 8)
  digitalWrite(HD_PIN, HIGH); // liberar
  Serial.println(">>> Calibración HD aplicada. Espera unos minutos para estabilizar.");
}

void loop() {
  // Si quieres forzar una calibración por software descomenta:
  //manualZeroCalibrate(); delay(60000); // evitar hacerlo continuamente

  unsigned long th = pulseIn(PWM_PIN, HIGH, 2000000); // microsegundos, timeout 1.2s
  unsigned long tl = pulseIn(PWM_PIN, LOW,  2000000);

  float ms_th = th / 1000.0;
  float ms_tl = tl / 1000.0;
  // Fórmula del datasheet:
  float ppm = RANGE_PPM * (ms_th - 2.0) / (ms_th + ms_tl - 4.0);

  Serial.print("TH(ms): "); Serial.print(ms_th,3);
  Serial.print("  TL(ms): "); Serial.print(ms_tl,3);
  Serial.print("  -> CO2 (ppm): "); Serial.println(ppm, 1);

  delay(1000); // lectura ~1s
}
