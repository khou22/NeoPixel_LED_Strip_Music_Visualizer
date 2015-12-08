# NeoPixel_LED_Strip_Music_Visualizer
Author: Kevin Hou <br />
Date: December 2, 2015 <br />
Arduino music visualizer that uses the NeoPixel LED strands to change colors, brightness, etc. in response to the music.

# How It Works
<ol>
  <li>The baseline frequencies are calibrated</li>
  <li>The average of the frequencies (relative to the baseline established) controls the brightness</li>
  <li>Once the average hits a certain level, the LED's change to a new random color</li>
  <li>Every 6 seconds the Arduino recallibrates itself (to account for song changes, etc.) to keep the music visualizer interesting</li>
</ol>
