# esphome_components
ESPhome Components from the little digger and Jens

We collected some (currently one) of our ESPhome components here to share with other diggers:

- KM271-WiFi is also described in detail in one of my [blog posts](https://the78mole.de/reverse-engineering-the-buderus-km217/)

## KM217 Wifi

### Overview
This component uses the hardware designed by the78mole to read interesting values from a buderus logamatic oil fired heating system.

 ![image](images/home-assistant-values.png)
 
### Usage
See https://esphome.io/components/external_components.html for information about integrating this into your esphome environemnt

To configure the component, see the included file buderus-km271.yaml.
If you are not interested in some of the provided values, just remove the respective entry in the the section "sensor" or "binary_sensor".
 
### Limitations
   * The software only provides a sub-set of the available data. Feel free to create a pull request to add data you want to see.
   * Changing of values (e.g. target temperatures) is not yet supported. This is planned for a later version.
 
### Notes by Jens
I'm working on this project as a hobby. My work on this software is in no way associated with a company. If you like to use it, or improve on it, feel free.
Use it at your own risk - it might work perfectly or it might not.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

### Advertisement by Jens
If you are in need of professional software engineering services, feel free to contact me. I've got good contacts to a ten-person embedded software and server software development team.
They are based in Germany and also provide coaching and support regarding continuous integration and test automation.
