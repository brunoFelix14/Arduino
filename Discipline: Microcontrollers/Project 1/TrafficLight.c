/* =============== Projet 1 - Semáforo =============== */
/*Diciplina: Microcontroladores - Engenharia de Computação 3*/
/*Professor: Marcio Afonso Soleira Grassi*/
/*Autor: Bruno Felix da Silva*/

bool pedestre = false;

void setup() 
{
  // Semáforo 1
  pinMode(5, OUTPUT); // Vermelho
  pinMode(6, OUTPUT); // Amarelo
  pinMode(7, OUTPUT); // Verde

  // Semáforo 2
  pinMode(4, OUTPUT); // Vermelho
  pinMode(3, OUTPUT); // Amarelo
  pinMode(2, OUTPUT); // Verde

  // Botão do pedestre
  pinMode(10, INPUT_PULLUP);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);

  Serial.begin(9600);
}

// Estado S0: Semáforo 1 vermelho, Semáforo 2 verde
void EstadoS0()
{
  digitalWrite(5, HIGH); // S1 vermelho
  digitalWrite(2, HIGH); // S2 verde

  // Espera 3s usando millis()
  unsigned long inicio = millis();
  while(millis() - inicio < 3000)
  {
    if(digitalRead(10) == LOW) 
    {
      pedestre = true; 
    }

    if(Serial.available())
    {
      String escolha = Serial.readStringUntil('\n');
      escolha.trim();

      if(escolha == "amarelo") 
      {
        EstadoS4();
      }
    }
  }
}

// Estado S1: Semáforo 1 vermelho, Semáforo 2 amarelo
void EstadoS1()
{
  digitalWrite(2, LOW);
  digitalWrite(5, HIGH); // S1 vermelho
  digitalWrite(3, HIGH); // S2 amarelo

  unsigned long inicio = millis();
  while(millis() - inicio < 3000)
  {
    if(digitalRead(10) == LOW) 
    {
      pedestre = true; 
    }

    if(Serial.available())
    {
      String escolha = Serial.readStringUntil('\n');
      escolha.trim();

      if(escolha == "amarelo") 
      {
        EstadoS4();
      }
    }
  }

  digitalWrite(3, LOW);
}

// Estado S2: Semáforo 1 verde, Semáforo 2 vermelho
void EstadoS2()
{
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);
  digitalWrite(7, HIGH); // S1 verde
  digitalWrite(4, HIGH); // S2 vermelho

  unsigned long inicio = millis();
  while(millis() - inicio < 3000)
  {
    if(digitalRead(10) == LOW) 
    {
      pedestre = true; 
    }

    if(Serial.available())
    {
      String escolha = Serial.readStringUntil('\n');
      escolha.trim();

      if(escolha == "amarelo") 
      {
        EstadoS4();
      }
    }
  }
}

// Estado S3: Semáforo 1 amarelo, Semáforo 2 vermelho
void EstadoS3()
{
  digitalWrite(7, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH); // S1 amarelo
  digitalWrite(4, HIGH); // S2 vermelho

  unsigned long inicio = millis();
  while(millis() - inicio < 3000)
  {
    if(digitalRead(10) == LOW) 
    {
      pedestre = true;
    }

    if(Serial.available())
    {
      String escolha = Serial.readStringUntil('\n');
      escolha.trim();

      if(escolha == "amarelo")
      {
        EstadoS4();
      } 
    }
  }

  digitalWrite(6, LOW);
  digitalWrite(4, LOW);
}

// Estado S4: modo amarelo piscando
void EstadoS4()
{
  Serial.println("Estado S4 ativado! Digite 'semáforo' para voltar.");
  while(true)
  { 
    digitalWrite(2, LOW); 
    digitalWrite(4, LOW); 
    digitalWrite(5, LOW); 
    digitalWrite(7, LOW);
    digitalWrite(6, HIGH); 
    digitalWrite(3, HIGH); 

    delay(500);

    digitalWrite(6, LOW); 
    digitalWrite(3, LOW); 

    delay(500);

    if(Serial.available() > 0)
    {
      String entrada = Serial.readStringUntil('\n');
      entrada.trim(); 

      if(entrada.equalsIgnoreCase("semáforo"))
      {
        Serial.println("Voltando ao modo normal...");
        break; 
      }
      else
      {
        Serial.println("Comando inválido, digite 'semáforo' para voltar.");
      }
    }
  }
}

void loop() 
{
  Serial.println("Insira 'amarelo' para ativar o EstadoS4 e 'semáforo' para voltar ao normal.");

  if(Serial.available())
  {
    String escolha = Serial.readStringUntil('\n');
    escolha.trim();

    if(escolha == "amarelo") 
    {
      EstadoS4();
    }
  }

  EstadoS0();
  EstadoS1();
  EstadoS2();
  EstadoS3();

  if(pedestre) 
  {
    // Deixa todos os semáforos das ruas em vermelho
    digitalWrite(5, HIGH); // S1 vermelho
    digitalWrite(6, LOW);  // S1 amarelo
    digitalWrite(7, LOW);  // S1 verde
    digitalWrite(4, HIGH); // S2 vermelho
    digitalWrite(3, LOW);  // S2 amarelo
    digitalWrite(2, LOW);  // S2 verde

    // Acende semáforo de pedestre verde
    digitalWrite(13, HIGH);
    digitalWrite(12, LOW);

    delay(8000); // Tempo para atravessar

    digitalWrite(4, LOW);
    // Volta semáforo de pedestre para vermelho
    digitalWrite(13, LOW);
    digitalWrite(12, HIGH);

    pedestre = false; 
  }
}
