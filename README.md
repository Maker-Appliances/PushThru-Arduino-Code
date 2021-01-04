This is the Arduino source code to make Push Thru work

#Push-Thru Coding Guide

## Your Push-Thru button needs to be loaded with some code before you can connect your Pantri account, this is the step by step guide on how to do it.

There are a few steps in this process, all of which will require a PC, Mac or computer of some kind. Before you start, you will need to have assembled your Push-Thru button and connected it to an Adafruit Huzzah ESP8266. Once you’ve done that… you’re good to go…

What you need:

* Assembled Push-Thru button (guide is here)
* Micro USB lead
* Computer
* Arduino IDE app ([found here](https://www.arduino.cc/en/software))

![](https://images.squarespace-cdn.com/content/v1/5c029f77ee1759938a3b5dd0/1548763765973-QG0PMBEH6W17WT7F2EM2/ke17ZwdGBToddI8pDm48kNiEM88mrzHRsd1mQ3bxVct7gQa3H78H3Y0txjaiv_0fDoOvxcdMmMKkDsyUqMSsMWxHk725yiiHCCLfrh8O1z4YTzHvnKhyp6Da-NYroOW3ZGjoBKy3azqku80C789l0s0XaMNjCqAzRibjnE_wBlkZ2axuMlPfqFLWy-3Tjp4nKScCHg1XF4aLsQJlo6oYbA/IMG_0564_batch.jpg?format=1000w)

##Download all the stuff

We love to use open source tech, it’s what we are all about. One of our favourite applications for programming our devices is the Arduino IDE. You will need to download; Arduino IDE, the libraries used in Push-Thru, the Adafruit board settings and the Push-Thru default code from Github . Don’t worry though…we will take you through it!

###Download and install the Arduino IDE

Arduino is an open source platform for makers and inventors like you. The make awesome programmable boards, and have a free and easy to use programming ‘environment’, the Arduino IDE.

![https://images.squarespace-cdn.com/content/v1/5c029f77ee1759938a3b5dd0/1548931128015-RJSL7C2EYQ64NDXIWYAS/ke17ZwdGBToddI8pDm48kK78QEXTH8U_h8zttH-XwRFZw-zPPgdn4jUwVcJE1ZvWQUxwkmyExglNqGp0IvTJZamWLI2zvYWH8K3-s_4yszcp2ryTI0HqTOaaUohrI8PIyVT2tnE36Rj3wuj3HoAj-B5kR_3Rcrrl1Cm6ebmb2mA/DownloadingArduinoIDE_Final.gif?format=2500w](https://images.squarespace-cdn.com/content/v1/5c029f77ee1759938a3b5dd0/1548931128015-RJSL7C2EYQ64NDXIWYAS/ke17ZwdGBToddI8pDm48kK78QEXTH8U_h8zttH-XwRFZw-zPPgdn4jUwVcJE1ZvWQUxwkmyExglNqGp0IvTJZamWLI2zvYWH8K3-s_4yszcp2ryTI0HqTOaaUohrI8PIyVT2tnE36Rj3wuj3HoAj-B5kR_3Rcrrl1Cm6ebmb2mA/DownloadingArduinoIDE_Final.gif?format=2500w)

*Go to [arduino.cc](https://www.arduino.cc/en/software) to get hold of the latest Arduino IDE for your desktop.*

##Add the Adafruit Huzzah ESP8266 board

The Arduino IDE has a really great way to add new programmable boards, the ‘Boards Manager’. This allows you to quickly add new Arduino compatible boards to your IDE!

![](https://images.squarespace-cdn.com/content/v1/5c029f77ee1759938a3b5dd0/1548858010165-DWUXC7GCITO3WIDP3YBV/ke17ZwdGBToddI8pDm48kJ0lej6MlCqKAUx1EqBpSQQUqsxRUqqbr1mOJYKfIPR7LoDQ9mXPOjoJoqy81S2I8N_N4V1vUb5AoIIIbLZhVYxCRW4BPu10St3TBAUQYVKcE79ZA1emBlttGqUBJ5k1Qhla88IYte9c1OHrE4ZEhBPbvKCViBqYtP1YD9ZsRUp_/Arduino_BoardManagerSetup.gif?format=2500w)

*Go to Tools > Board > Board Manager, then search for ‘ESP8266’ make sure to use 2.4.2, not the beta versions.*

##Add the libraries needed for your Push-Thru
Libraries are essentially lists of rules and instructions that our code refers to to make your Push-Thru button work properly. Without them, the Arduino IDE will give you a few errors… because the IDE doesn’t know what the code does/is.

There are two libraries that you will need, and these can be added in a similar way to how you added the Adafruit Huzzah ESP8266 board.

The two libraries are: 

1. ArduinoJSON
2. WiFi

![](https://images.squarespace-cdn.com/content/v1/5c029f77ee1759938a3b5dd0/1548932413774-CSYY9MHJZI2PJ6EHJVLU/ke17ZwdGBToddI8pDm48kK78QEXTH8U_h8zttH-XwRFZw-zPPgdn4jUwVcJE1ZvWQUxwkmyExglNqGp0IvTJZamWLI2zvYWH8K3-s_4yszcp2ryTI0HqTOaaUohrI8PIyVT2tnE36Rj3wuj3HoAj-B5kR_3Rcrrl1Cm6ebmb2mA/Arduino_SettingUpLibrariesPushThru.gif?format=2500w)

*Go to Sketch > Include Library > Manage Libraries… to add new libraries to the Arduino IDE*

##Download the code for your Push-Thru
Github is a website that allows us to share all of our open source projects and code. You can head over to our repositories and get a copy of the code to put onto your Push-Thru button.

![](https://images.squarespace-cdn.com/content/v1/5c029f77ee1759938a3b5dd0/1548858733423-S3QWUJLCG49BLVMOKIP5/ke17ZwdGBToddI8pDm48kJ0lej6MlCqKAUx1EqBpSQQUqsxRUqqbr1mOJYKfIPR7LoDQ9mXPOjoJoqy81S2I8N_N4V1vUb5AoIIIbLZhVYxCRW4BPu10St3TBAUQYVKcE79ZA1emBlttGqUBJ5k1Qhla88IYte9c1OHrE4ZEhBPbvKCViBqYtP1YD9ZsRUp_/Arduino_DownloadingGitHubCode.gif?format=2500w)

*Click on the green* **↧ CODE ↓** *button at the top of this page to get the code for your button.  If you don't know how git repo's work, just select Download ZIP from the dropdown.*

##Setup your Pantri Device
You will need to download a Pantri app and have a Pantri account for this bit.  Visit the app store link on the Pantri website [https://www.pantri.net](https://www.pantri.net) for your smartphone operating system and choose an app that takes your fancy.

Navigate through to add a device.  In there you should see Maker Appliances as an option.  If you select that, you should now have the ability to configure the device.  


##Load the code and push that button!
Now all we need to do is to modify the code (adding your unique device ID and your wifi settings ), add the MAC address to the Pantri Dashboard, and test the button!

![](https://images.squarespace-cdn.com/content/v1/5c029f77ee1759938a3b5dd0/1548946433168-ITYLPFT709N8TIZKV7P1/ke17ZwdGBToddI8pDm48kK78QEXTH8U_h8zttH-XwRFZw-zPPgdn4jUwVcJE1ZvWQUxwkmyExglNqGp0IvTJZamWLI2zvYWH8K3-s_4yszcp2ryTI0HqTOaaUohrI8PIyVT2tnE36Rj3wuj3HoAj-B5kR_3Rcrrl1Cm6ebmb2mA/PushinthePushThruSMALL.gif?format=2500w)