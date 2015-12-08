# NeoPixel_LED_Strip_Music_Visualizer
Author: <i>Kevin Hou</i> <br />
Date: <i>December 2, 2015</i> <br />
Description: <i>Arduino music visualizer that uses the NeoPixel LED strands to change colors, brightness, etc. in response to the music.</i>

# How It Works
<ol>
  <li>The baseline frequencies are calibrated</li>
  <li>The average of the frequencies (relative to the baseline established) controls the brightness</li>
  <li>Once the average hits a certain level, the LED's change to a new random color</li>
  <li>Every 6 seconds the Arduino recallibrates itself (to account for song changes, etc.) to keep the music visualizer interesting</li>
</ol>
