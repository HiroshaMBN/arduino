#include <Servo.h>
#include <AFMotor.h>
#define LINE_BUFFER_LENGTH 512
char STEP = MICROSTEP ;
// Servo position for Up and Down 
Const int penZUp = 130;
Const int penZDown = 83;
// Servo on PWM pin 10
Const int penServoPin =10 ;
// Should be right for DVD steppers, but is not too important here
Const int stepsPerRevolution = 50; 
// create servo object to control a servo 
Servo penServo;  
// Initialize steppers for X- and Y-axis using this Arduino pins for the L293D H-bridge
AF_Stepper myStepperY(stepsPerRevolution,1);            
AF_Stepper myStepperX(stepsPerRevolution,2);  
/* Structures, global variables    */
Struct point { 
Float x; 
Float y; 
Float z; 
};

// Current position of plothead
Struct point actuatorPos;
//  Drawing settings, should be OK
Float StepInc = 1;
Int StepDelay = 1;
Int LineDelay =2;
Int penDelay = 50;
// Motor steps to go 1 millimeter.
// Use test sketch to go 100 steps. Measure the length of line. 
// Calculate steps per mm. Enter here.
Float StepsPerMillimeterX =64;
Float StepsPerMillimeterY = 100.0;
// Drawing robot limits, in mm
// OK to start with. Could go up to 50 mm if calibrated well. 
Float Xmin = 0;
Float Xmax = 40;
Float Ymin = 0;
Float Ymax =40;
Float Zmin = 0;
Float Zmax = 1;
Float Xpos = Xmin;
Float Ypos = Ymin;
Float Zpos = Zmax; 
// Set to true to get debug output.
Boolean verbose = false;
//  Needs to interpret 
//  G1 for moving
//  G4 P300 (wait 150ms)
//  M300 S30 (pen down)
//  M300 S50 (pen up)
//  Discard anything with a 
//  Discard any other command!
Void setup() {
Serial.begin( 9600 );
penServo.attach(penServoPin);
penServo.write(penZUp);
delay(100);
// Decrease if necessary
myStepperX.setSpeed(600);
myStepperY.setSpeed(600);  
//  Set & move to initial default position
// TBD
//  Notifications!!!
Serial.println('Min CNC Plotter alive  kicking!');
Serial.print('X range is from'); 
Serial.print(Xmin); 
Serial.print('to'); 
Serial.print(Xmax); 
Serial.println('mm.'); 
Serial.print('Y range is from'); 
Serial.print(Ymin); 
Serial.print('to'); 
Serial.print(Ymax); 
Serial.println('mm.'); 
}
Void loop() 
{
Delay(100);
Char line[ LINE_BUFFER_LENGTH ];
Char c;
Int lineIndex;
Bool lineIsComment, lineSemiColon;
lineIndex = 0;
lineSemiColon = false;
lineIsComment = false;
while (1) {
// Serial reception – Mostly from Grbl, added semicolon support
While ( Serial.available()>0 ) {
C = Serial.read();
If (( c == "\n") || (c == "\r") ) {             // End of line reached
If ( lineIndex > 0 ) {                        // Line is complete. Then execute!
Line[ lineIndex ] = "\0";                   // Terminate string
If (verbose) { 
Serial.print('Received :'); 
Serial.println( line ); 
}
processIncomingLine( line, lineIndex );
lineIndex = 0;
} 
Else { 
// Empty or comment line. Skip block.
}
lineIsComment = false;
lineSemiColon = false;
Serial.println('ok');    
} 
else {
If ( (lineIsComment) || (lineSemiColon) ) {   // Throw away all comment characters
If ( c == ")" )  lineIsComment = false;     // End of comment. Resume line.
} 
else {
If ( c <= " " ) {                           // Throw away whitepace and control characters
} 
else if ( c == "/" ) {                    // Block delete not supported. Ignore character.
} 
else if ( c == "(" ) {                    // Enable comments flag and ignore all characters until ‘)’ or EOL.
lineIsComment = true;
} 
else if ( c == ";" ) {
lineSemiColon = true;
} 
else if ( lineIndex >= LINE_BUFFER_LENGTH-1 ) {
Serial.println('ERROR – lineBuffer overflow');
lineIsComment = false;
lineSemiColon = false;
} 
else if ( c >= "a" && c <= "z" ) {        // Upcase lowercase
Line[ lineIndex++ ] = c-"a"+"A";
} 
else {
Line[ lineIndex++ ] = c;
}
}
}
}
}
}
Void processIncomingLine( char* line, int charNB ) {
Int currentIndex = 0;
Char buffer[ 64 ];                                 // Hope that 64 is enough for 1 parameter
Struct point newPos;
newPos.x = 0.0;
newPos.y = 0.0;
//  Needs to interpret 
//  G1 for moving
//  G4 P300 (wait 150ms)
//  G1 X60 Y30
//  G1 X30 Y50
//  M300 S30 (pen down)
//  M300 S50 (pen up)
//  Discard anything with a (
//  Discard any other command!
While( currentIndex < charNB ) {
Switch ( line[ currentIndex++ ] ) {              // Select command, if any
Case "U":
penUp(); 
break;
case "D":
penDown(); 
break;
case "G":
buffer[0] = line[ currentIndex++ ];          // /!\ Dirty – Only works with 2 digit commands
//      buffer[1] = line[ currentIndex++ ];
//      buffer[2] = "\0";
Buffer[1] = "\0";
Switch ( atoi( buffer ) ){                   // Select G command
Case 0:                                   // G00 & G01 – Movement or fast movement. Same here
Case 1:
// /!\ Dirty – Suppose that X is before Y
Char* indexX = strchr( line+currentIndex, "X" );  // Get X/Y position in the string (if any)
Char* indexY = strchr( line+currentIndex, "Y" );
if ( indexY <= 0 ) {
newPos.x = atof( indexX + 1); 
newPos.y = actuatorPos.y;
} 
Else if ( indexX <= 0 ) {
newPos.y = atof( indexY + 1);
newPos.x = actuatorPos.x;
} 
else {
newPos.y = atof( indexY + 1);
indexY = "\0";
newPos.x = atof( indexX + 1);
}
drawLine(newPos.x, newPos.y );
//Serial.println(“ok”);
actuatorPos.x = newPos.x;
actuatorPos.y = newPos.y;
break;
}
Break;
Case "M":
Buffer[0] = line[ currentIndex++ ];        // /!\ Dirty – Only works with 3 digit commands
Buffer[1] = line[ currentIndex++ ];
Buffer[2] = line[ currentIndex++ ];
Buffer[3] = "\0";
Switch ( atoi( buffer ) ){
Case 300:
{
Char* indexS = strchr( line+currentIndex, "S" );
Float Spos = atof( indexS + 1);
//Serial.println(“ok”);
if (Spos == 30) { 
penDown(); 
}
if (Spos == 50) { 
penUp(); 
}
Break;
}
Case 114:                                // M114 – Repport position
Serial.print('Absolute position : X = ');
Serial.print( actuatorPos.x );
Serial.print('  -  Y = ');
Serial.println( actuatorPos.y );
Break;
Default:
Serial.print('Command_not recognized : M');
Serial.println( buffer );
}
}
}
}
/*******************************
 * Draw a line from (x0;y0) to (x1;y1).
 * int (x1;y1) : Starting coordinates
 * int (x2;y2) : Ending coordinates
 **********************************/
Void drawLine(float x1, float y1) {
if (verbose)
{
Serial.print('fx1, fy1: ');
Serial.print(x1);
Serial.print(',');
Serial.print(y1);
Serial.println("");
}  
//  Bring instructions within limits
if (x1 >= Xmax) { 
X1 = Xmax; 
}
if (x1 <= Xmin) { 
X1 = Xmin; 
}
if (y1 >= Ymax) { 
Y1 = Ymax; 
}
if (y1 <= Ymin) { 
Y1 = Ymin; 
}
if (verbose)
{
Serial.print('Xpos, Ypos:');
Serial.print(Xpos);
Serial.print(',');
Serial.print(Ypos);
Serial.println("");
}
if (verbose)
{
Serial.print('x1, y1: ');
Serial.print(x1);
Serial.print(',');
Serial.print(y1);
Serial.println("");
}
//  Convert coordinates to steps
X1 = (int)(x1*StepsPerMillimeterX);
Y1 = (int)(y1*StepsPerMillimeterY);
Float x0 = Xpos;
Float y0 = Ypos;
//  Let’s find out the change for the coordinates
Long dx = abs(x1-x0);
Long dy = abs(y1-y0);
Int sx = x0<x1 ? StepInc : -StepInc;
Int sy = y0<y1 ? StepInc : -StepInc;
Long i;
Long over = 0;
If (dx > dy) {
For (i=0; i<dx; ++i) {
myStepperX.onestep(sx,STEP);
over+=dy;
if (over>=dx) {
over-=dx;
myStepperY.onestep(sy,STEP);
}
Delay(StepDelay);
}
}
else {
For (i=0; i<dy; ++i) {
myStepperY.onestep(sy,STEP);
over+=dx;
if (over>=dy) {
over-=dy;
myStepperX.onestep(sx,STEP);
}
Delay(StepDelay);
}    
}
if (verbose)
{
Serial.print('dx,dy:');
Serial.print(dx);
Serial.print(',');
Serial.print(dy);
Serial.println("");
}
if (verbose)
{
Serial.print('Going to ('));
Serial.print(x0);
Serial.print(',');
Serial.print(y0);
Serial.println("");
}
//  Delay before any next lines are submitted
Delay(LineDelay);
//  Update the positions
Xpos = x1;
Ypos = y1;
}
//  Raises pen
Void penUp() { 
penServo.write(penZUp); 
delay(penDelay); 
Zpos=Zmax; 
digitalWrite(15, LOW);
digitalWrite(16, HIGH);
if (verbose) { 
Serial.println('Pen up!'); 
} 
}
//  Lowers pen
Void penDown(){
penServo.write(penZDown);
delay(penDelay); 
Zpos=Zmin; 
digitalWrite(15,HIGH);
digitalWrite(16,LOW);
if(verbose){
Serial.println('Pen down.');}
} 
