#include <Encoder.h>
#include <EEPROM.h>
#include <Bounce.h>

int32_t oldPosition;
uint32_t previousMillis;

//rotary encoder divider to adjust speed
//EEPROM address
#define ADDR_ROTDIV 0
uint8_t rotary_div;

//encoder defines
//if movement is reversed, swap these (or the encoder wires)
#define ENC_A 0
#define ENC_B 1

//button defines
#define BTN_ROTDIV 2
#define BTN_START 3
#define BTN_CREDIT1 4
#define BTN_CREDIT2 5
#define BTN_SETTINGS 6
#define BTN_PAUSE 7
#define BTN_SKIP 8
#define BTN_RESTART 9
#define BTN_RESET 10
#define BTN_UNK 11
#define BTN_CUSTOM1 14
#define BTN_CUSTOM2 15


// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(ENC_B, ENC_A);
//   avoid using pins with LEDs attached


// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
// 10 = 10 ms debounce time which is appropriate for most
// mechanical pushbuttons
// if a button is too "sensitive" to rapid touch, you can
// increase this time
Bounce btn_credit1 = Bounce(BTN_CREDIT1, 10);
Bounce btn_credit2 = Bounce(BTN_CREDIT2, 10);
Bounce btn_start = Bounce(BTN_START, 10);
Bounce btn_settings = Bounce(BTN_SETTINGS, 10);
Bounce btn_pause = Bounce(BTN_PAUSE, 10);
Bounce btn_skip = Bounce(BTN_SKIP, 10);
Bounce btn_reset = Bounce(BTN_RESET, 10);
Bounce btn_restart = Bounce(BTN_RESTART, 10);
Bounce btn_unk = Bounce(BTN_UNK, 10);
Bounce btn_rotdiv = Bounce(BTN_ROTDIV, 10);
Bounce btn_custom1 = Bounce(BTN_CUSTOM1, 10);
Bounce btn_custom2 = Bounce(BTN_CUSTOM2, 10);

void setup()
{
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!
  pinMode(BTN_CREDIT1, INPUT_PULLUP);
  pinMode(BTN_CREDIT2, INPUT_PULLUP);
  pinMode(BTN_START, INPUT_PULLUP);
  pinMode(BTN_SETTINGS, INPUT_PULLUP);
  pinMode(BTN_PAUSE, INPUT_PULLUP);
  pinMode(BTN_SKIP, INPUT_PULLUP);
  pinMode(BTN_RESET, INPUT_PULLUP);
  pinMode(BTN_RESTART, INPUT_PULLUP);
  pinMode(BTN_UNK, INPUT_PULLUP);
  pinMode(BTN_ROTDIV, INPUT_PULLUP);
  pinMode(BTN_CUSTOM1, INPUT_PULLUP);
  pinMode(BTN_CUSTOM2, INPUT_PULLUP);

  //read rotary divider value from EEPROM
  rotary_div=EEPROM.read(ADDR_ROTDIV);
  //reset divider to 1 if button pressed at startup or EEPROM value outside valid range
  if ((digitalRead(BTN_ROTDIV)==0)||(rotary_div<1)||(rotary_div>10))
  {
    rotary_div=1;
    EEPROM.write(ADDR_ROTDIV, rotary_div);
  }

  Serial.begin(9600);

  oldPosition = myEnc.read()/rotary_div; //set initial rotary position
}

void loop()
{
  int32_t newPosition;

  newPosition = myEnc.read()/rotary_div;
  if (newPosition != oldPosition)
  {
    Mouse.move(newPosition-oldPosition, 0);
    oldPosition = newPosition;
    Serial.println(newPosition);
  }

  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  btn_credit1.update();
  btn_credit2.update();
  btn_start.update();
  btn_settings.update();
  btn_pause.update();
  btn_skip.update();
  btn_reset.update();
  btn_restart.update();
  btn_unk.update();
  btn_rotdiv.update();
  btn_custom1.update();
  btn_custom2.update();
  
  // Check each button for "falling" edge.
  // Type a message on the Keyboard when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)
  if (btn_credit1.fallingEdge())
    Keyboard.press(KEY_1);
  if (btn_credit2.fallingEdge())
    Keyboard.press(KEY_2);
  if (btn_start.fallingEdge())
    Keyboard.press(KEY_3);
  if (btn_settings.fallingEdge())
    Keyboard.press(KEY_S);
  if (btn_pause.fallingEdge())
    Keyboard.press(KEY_P);
  if (btn_skip.fallingEdge())
    Keyboard.press(KEY_RIGHT);
  if (btn_reset.fallingEdge())
    Keyboard.press(KEY_0);
  if (btn_restart.fallingEdge())
    Keyboard.press(KEY_ESC);
  if (btn_unk.fallingEdge())
    Keyboard.press(KEY_F);
  if (btn_rotdiv.fallingEdge())
    previousMillis = millis();
  if (btn_custom1.fallingEdge())
  {
    //custom key 1 (currently undefined)
  }
  if (btn_custom2.fallingEdge())
  {
    //custom key 2 (currently undefined)
  }

  // Check each button for "rising" edge
  // Type a message on the Keyboard when each button releases.
  // For many types of projects, you only care when the button
  // is pressed and the release isn't needed.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)
  if (btn_credit1.risingEdge())
    Keyboard.release(KEY_1);
  if (btn_credit2.risingEdge())
    Keyboard.release(KEY_2);
  if (btn_start.risingEdge())
    Keyboard.release(KEY_3);
  if (btn_settings.risingEdge())
    Keyboard.release(KEY_S);
  if (btn_pause.risingEdge())
    Keyboard.release(KEY_P);
  if (btn_skip.risingEdge())
    Keyboard.release(KEY_RIGHT);
  if (btn_reset.risingEdge())
    Keyboard.release(KEY_0);
  if (btn_restart.risingEdge())
    Keyboard.release(KEY_ESC);
  if (btn_unk.risingEdge())
    Keyboard.release(KEY_F);
  if (btn_rotdiv.risingEdge())
  {
    if ((millis() - previousMillis) >= 2000)
      EEPROM.write(ADDR_ROTDIV, rotary_div);
    else
    {
      rotary_div++;
      if (rotary_div > 10)
        rotary_div=1;
    }
  }
  if (btn_custom1.risingEdge())
  {
    //custom key 1 (currently undefined)
  }
  if (btn_custom2.risingEdge())
  {
    //custom key 2 (currently undefined)
  }
}
