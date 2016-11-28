
/*
  Codigo de muestra para la decodificacion de los datos del puerto iBUS
  del receptor FS-iA6B
*/

bool trama_completa = 0;
byte trama[32];

void setup()
{
  // Iniciacion de los puertos seriales
  Serial.begin(250000); //Puerto de comunicacion con la PC
  Serial1.begin(115200);
  Serial.println("Prueba de lectura de puerto iBUS");
  delay(1500);

}

void loop()
{
  // Esperar datos provinientes del FlySky FS-iA6B
  if (Serial1.available())
  {
    for (int i = 0; i < 32; i++)
    {
      if (i == 31) {
        trama[i] = Serial1.read();
      }
      else
      {
        trama[i] = trama [i + 1];
      }
    }
    if (trama[0] == 0x20 & trama[1] == 0x40 & trama[28] == 0xDC & trama[29] == 0x05)
      {
        for (int i = 0; i < 32; i++)
        {
          Serial.print(trama[i], HEX);
          if (i < 31)Serial.print(", ");
        }
        Serial.println();
        trama_completa = 0;
        //limpieza de los datos de sincronizacion
        trama[0] = 0;
        trama[1] = 0;
        trama[28] = 0;
        trama[29] = 0;
      }
  }

}

