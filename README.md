---

# Proyecto: **Consulta de Cotización del Dólar con ESP8266**

Este proyecto utiliza un ESP8266 para consultar la cotización del dólar desde una API REST y mostrarla en un display LCD. La cotización incluye varios tipos de dólar, como el oficial, blue, bolsa y tarjeta.

---

## 🛠️ **Requisitos**

### Hardware
- **ESP8266** (NodeMCU o similar).
- **Pantalla LCD I2C** (1602 o 2004).
- Cables y conexiones necesarias.

### Software
- **Arduino IDE** (v1.8 o superior).
- Librerías:
  - [ArduinoJson](https://arduinojson.org/).
  - [ESP8266WiFi](https://arduino-esp8266.readthedocs.io/).
  - [ESP8266HTTPClient](https://arduino-esp8266.readthedocs.io/).
  - [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C).

---

## ⚙️ **Configuración**

1. **Clona el repositorio**:
   ```bash
   git clone https://github.com/tute-avalos/dolar-api-client.git
   ```
2. **Configura el WiFi**:  
   Modifica las constantes `WIFI_SSID` y `WIFI_PASSWORD` en el código para que coincidan con tu red WiFi.

3. **Sube el código al ESP8266**:
   - Conecta tu ESP8266 a tu PC.
   - Configura la tarjeta en Arduino IDE (`Herramientas > Placa > NodeMCU 1.0`).
   - Selecciona el puerto correcto (`Herramientas > Puerto`).
   - Carga el código en el ESP8266.

4. **Conecta el hardware**:
   - Conecta el LCD al ESP8266 mediante los pines I2C (SDA y SCL).

---

## 🖥️ **Funcionamiento**

1. Al iniciar, el ESP8266 se conecta a la red WiFi configurada.
2. Consulta las cotizaciones de dólar desde la API [DolarAPI](https://dolarapi.com).
3. Muestra la cotización de compra y venta de cada tipo de dólar en la pantalla LCD.
4. Cambia automáticamente entre los diferentes tipos de dólar cada 10 segundos.

---

## 🛡️ **Advertencias**

- El código utiliza `client.setInsecure()`, lo cual omite la validación del certificado SSL. Esto **no es recomendado** para producción.
- Verifica que la dirección I2C del LCD (`0x27`) sea la correcta. Puedes usar un escáner I2C si es necesario.

---

## 📝 **Personalización**

- Cambia el intervalo de consulta modificando `INTERVALO_CONSULTA` (en milisegundos).
- Ajusta los tipos de dólar a consultar modificando el arreglo `DOLARES`.

---

## 📜 **Licencia**

Este proyecto se distribuye bajo la [Licencia MIT](LICENSE).

---

Si necesitas ayuda, no dudes en abrir un [issue](https://github.com/tu-usuario/tu-repositorio/issues). 😊

