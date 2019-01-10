# Swearing-Plants
An email notification service that notifies you when a plant needs to be watered. I made this for fun. It's vulgar, because I thought it would be funny if my basil cussed me out for forgetting to water it, instead of just dying.

This is a NodeMCU based notification service that can send emails informing you when a plant's soil is getting too dry. It checks the soil once an hour and only notifies you when it's too dry. The notification uses foaas (Fuck off as a Service) to insult you for forgetting to water your plant. 

To set up your own, you need :
1 NodeMCU
1 HONG111 TE215 Soil Moisture Sensor
1 Breadboard/hole-through PCB board
Wires

Modify the Arduino code to have your Wifi information. Netword SSID and Password. Change the email settings. Both the sent to and sent from settings. I recommend making a gmail account dedicated to sending notification emails for the sent from email. Make sure to set the security settings to allow access from less secure sources.
