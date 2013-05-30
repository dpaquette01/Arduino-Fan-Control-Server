#include <OneWire.h>
#include <DallasTemperature.h>
#include <SPI.h>
#include <Ethernet.h>


#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

byte mac[] = { 
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,1,3); // The IP address will be dependent on your local network:
String userIP = "http://192.168.1.3/"; //ip address in string format, can be a global IP or local(same as other ip most of the time)
// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
int count = 0;
int countOne = 0;
float small = 100;
float large = 0;
float autoCount = 0;
String fanStat = "Auto";
float data;
String readString = ""; 
boolean man = false;

int autoTempValue = 70;

void setup() {
  sensors.begin();
  pinMode(6, OUTPUT);     
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  sensors.requestTemperatures(); // Send the command to get temperatures
    data = DallasTemperature::toFahrenheit(sensors.getTempCByIndex(0));
    delay(.1);
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    
    countOne++;
    if(countOne == 2)
    {
      count++;
      countOne = 0;
    }
 
    // an http request ends with a blank line
   

    while (client.connected()) {
      if (client.available()) {

         char c = client.read();
        //read char by char HTTP request
        if (readString.length() < 75) {

          //store characters to string 
          readString += c; 
          
          //Serial.print(c);
        } 

        //if HTTP request has ended
        if (c == '\n') {
          if(readString.indexOf("on") >0)//checks for on
          {
            digitalWrite(6,HIGH);
            man = true;
            fanStat = "On";
            
          }
          else if(readString.indexOf("off") >0)//checks for off
          {
           digitalWrite(6,LOW);
             man = true;
            fanStat = "Off";
           
          }
          else if(readString.indexOf("auto") >0)//checks for off
          {
            man = false;
         fanStat = "Auto";
          }
   
     if(data >= autoTempValue && man == false)
    {
      digitalWrite(6,HIGH);
      fanStat = "Auto-ON";

    }
    
    else if(data < autoTempValue && man == false)
    {
      digitalWrite(6,LOW);
      fanStat = "Auto-OFF";

    }

        // send a standard http response header
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connnection: close");
        client.println();
        client.println("<!DOCTYPE HTML>");
        client.println("<html>");
  
//client.println("<STYLE><!--a{text-decoration:none;color : white;}--></STYLE>");
        client.println("<body style='font-family:Helvetica, Geneva, Tahoma, sans-serif;'>");
        //client.println(" <meta name='apple-mobile-web-app-capable' content='yes' />");
        // add a meta refresh tag, so the browser pulls again every 5 seconds:
        //client.println("<meta http-equiv=\"refresh\" content=\"5\">");
        client.println("<title>Arduino Fan Web Server </title>");
                client.println("<body bgcolor='#FFFFFF'>");
        

client.println("<center>");
client.print("<font size='5'>");
        client.print("Paquette Home");
         client.print("</font>");
        client.println("</center>");
        client.println("<body text='FFFFF'>");

        client.println("<hr noshade size=1 width='100%' align=center  HR COLOR='black'>");
        

        //client.println("<script type='text/javascript'>");
        //client.println("<!--");

        //client.println("if ((navigator.userAgent.indexOf('iPhone') != -1) || (navigator.userAgent.indexOf('iPod') != -1)){");  
        //client.println("document.body.background = 'http://www.mbtheme.com/uploads/allimg/c120710/1341Y549321E0-14M1.jpg';");
//client.println("document.body.style.backgroundColor='#808080'");
//client.println("window.onload = function() {");
    //client.println("setTimeout(function() { window.scrollTo(0, 1) }, 100);");
//client.println("};");
        //client.println("}");
        //client.println("else { document.body.style.backgroundColor='#2E2E2E'");
        //client.println("}");

       // client.println("//-->");
        //client.println("</script>");
        
        
        
        client.println("<script type='text/javascript'>  window.onload = function() {  setTimeout(function() { window.scrollTo(0, 1) }, 100);   };</script>");
           client.println("<br />");
              client.println("<br />");
client.println("<center>");
client.print("<font size='7'>");
client.println("<div style='background-color:#3579DF;width:200px;'>");
 client.println("<a href='"+ userIP +"' STYLE='text-decoration:none; color:white;'>");
 client.print(data);
 client.print("&degF");
 client.println("</a>");

        
        client.print("</font>");
        client.println("</div>");
client.println("</center>");
        


        client.println("<link rel='apple-touch-icon' href='http://modmyi.com/attachments/forums/iphone-4-4s-new-skins-themes-launches/530090d1307698205-buuf-iphone-4-climate.png'/>");

        client.println("<meta name='viewport' content='width=320, initial-scale=1.0, maximum-scale=1.0, user-scalable=0'/>");   


      

   


    client.println("<br />");
         client.println("<center>");
        client.print("<FONT COLOR='#FFD8E1'>");
        client.println("Max Temp:");
        client.print(large);
      client.print("</FONT>");
        client.print("<FONT COLOR='#FFD8E1'>&degF</FONT>");
        client.println("<br />"); 

        
        client.print("<FONT COLOR='#D8F7FF'>");
        client.println("Min Temp:");
        client.print(small);
      client.print("</FONT>");
     
        client.print("<FONT COLOR='#D8F7FF'>&degF</FONT>");
         client.println("</center>");
  client.println("<br />"); 
        client.println("<br />");
        client.println("<br />");
client.println("<center>");
client.print("<font size='5'>");
        client.print("Fan Status: ");
        client.print(fanStat);
        client.println("<br />"); 
        client.println("<a href=\'"+userIP+"?on'><button>On</button></a>"); 
        
          client.println("<a href=\'"+userIP+"?off'><button>Off</button></a>");
         client.println("<a href=\'"+userIP+"?auto'><button>Auto</button></a>"); 
         client.print("</font>");
        client.println("</center>");

        client.println("<br />");

 client.println("<br />"); 


client.println("<hr noshade size=1 width='100%' align=center  HR COLOR='white'>");

        client.print("<font size='3'>Page Views:</font>");
         client.print("<font size='3'>");
        client.print(count);

        client.print("</font>");

        client.println("</html>");
        
        break;
        readString = "";
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:

    client.stop();
    readString = "";
  }

  if (autoCount > 100){
    sensors.requestTemperatures(); // Send the command to get temperatures
    data = DallasTemperature::toFahrenheit(sensors.getTempCByIndex(0));
    delay(.1);
    if (data < small)
    {
      small = data;
    }

    if( data > large)
    {
      large = data;
    }
    if(data > autoTempValue && man == false)
    {
      digitalWrite(6,HIGH);
      fanStat = "Auto-ON";
    }
    
    if(data < autoTempValue && man == false)
    {
      digitalWrite(6,LOW);
      fanStat = "Auto-OFF";
    }
    readString="";
    autoCount = 0;
  }
  autoCount = autoCount + .001;
}


