# Raspberry Pi Installation

### Download Raspberry Pi Imager

https://www.raspberrypi.com/software/

### Install RPi OS on an SD Card

- Click **CHOOSE DEVICE** and select **Raspberry Pi 3**

- Click **CHOOSE OS** and select **Raspberry Pi OS (other)** -> **Raspberry Pi OS (Legacy, 64-bit) Lite**

- Click **CHOOSE STORAGE** and select an SD Card

- Click **NEXT** then click **EDIT SETTINGS**

- Edit the following settings

   -  Set hostname

   -  Set username and password

   -  Configure wireless LAN

      -  Wireless LAN country: TH

   -  Set locale settings

      -  Time zone: Asia/Bangkok

- Click **SAVE** then click **YES**

### Configuring Wi-Fi later

- Using **Raspberry Pi Software Configuration Tool**
 
  ```sh
  sudo raspi-config
  ```

- Go to **System Options** -> **Wireless LAN**

# Linux Basics

### Basic commands

```sh
ls
cd
pwd
mkdir
rmdir
rm
cp
mv
sudo
reboot
```

### Basic utilities

```sh
ifconfig wlan0
ip address show dev wlan0
man
cat
grep
nano
vi, vim
top, htop
```

# Install Docker

- Using the installation script

  ```sh
  curl https://get.docker.com | sh
  ```

- Add the current user to the `docker` group

  ```sh
  sudo usermod -aG docker $USER

  newgrp docker
  ```

- Basic Docker commands

  ```sh
  docker images
  docker pull hello-world
  docker run --rm hello-world
  docker ps [-a]
  docker stop
  docker [container] rm <container-name>
  docker compose up [-d]
  docker compose down
  docker network ls
  ```

# MQTT Basics

### MQTT concepts

- MQTT Essentials Guide and eBook (HiveMQ)

  https://www.hivemq.com/resources/content/download-mqtt-ebook/

  https://www.youtube.com/playlist?list=PLRkdoPznE1EMXLW6XoYLGd4uUaB6wB0wd

- Publisher and Subscriber architecture

  - Using MQTT client library

    - Publisher - generates messages

    - Subscriber - receives messages

  - Decoupling

    - Space - publisher and subscriber do not need to know each other

    - Time - publisher and subscriber do not need to run at the same time

  - Message Filtering based on the topic

- MQTT Broker

  - Receives messages from publishers and distributes to subscribers

  - Client session management

  - Client authentication and authorization

  - Examples

    - Eclipse Mosquitto

    - EMQ X

    - HiveMQ

- Topics

  - Hierarchical, each level is separated by a forward slash (`/`)

    - e.g. `home/bedroom/temperature`

    - Avoid leading slash as this introduces an unnecessary topic level with a zero character at the front

  - Case-sensitive

  - Wildcards subscription

    - **Plus (+)** - Single Level

      - e.g. `home/+/temperature`

    - **Hash (#)** - Multi Level

      - e.g. `home/#` -> subscribe to all messages that start with `home`

      - Does not include topics starting with `$` symbol

- Quality of Service (QoS)

  - **QoS 0** - At most once
  
  - **QoS 1** - At least once
  
  - **QoS 2** - Exactly once

- Retained Message

- Last Will and Testament (LWT), publish a message to a specified topic if it unexpectedly disconnects

### Running an MQTT broker (Mosquitto)

- Create a directory at `/home/pi/docker/mosquitto`

- Create `/home/pi/docker/mosquitto/docker-compose.yml` file

  ```yaml
  version: "3.9"
  name: iot-module-mqtt
  services:
    server:
      image: eclipse-mosquitto:2.0.18
      restart: always
      networks:
        - iot-module-net
      ports:
        - 1883:1883
      volumes:
        - ./config/mosquitto.conf:/mosquitto/config/mosquitto.conf:ro
  
  networks:
    iot-module-net:
      driver: bridge
  ```

- Create `/home/pi/docker/mosquitto/config/mosquitto.conf` file

  ```conf
  per_listener_settings true
  persistence false
  
  listener 1883 0.0.0.0
  allow_anonymous true
  allow_zero_length_clientid true
  use_username_as_clientid false
  ```

- Start the MQTT broker

  ```sh
  docker compose up -d
  ```

### Testing the MQTT broker

- Subscribe

  ```sh
  docker exec -it iot-module-mqtt-server-1 mosquitto_sub -v -t "#"
  ```

- Publish

  ```sh
  docker exec -it iot-module-mqtt-server-1 mosquitto_pub -t "test/greeting" -m "Hello, World!"

  docker exec -it iot-module-mqtt-server-1 mosquitto_pub -h 172.30.81.23 -t "test/greeting" -m "Hello, World!"
  ```

- Try **MQTT Explorer** https://mqtt-explorer.com/

### Using MQTT client on ESP32

- Install Arduino library **PubSubClient** by Nick O'Leary

- Library usage demo - `esp32/mqtt-client.ino`

# Node-RED

### Install Node-RED on host (RPi)

- Using the installation script

  ```sh
  bash <(curl -sL https://raw.githubusercontent.com/node-red/linux-installers/master/deb/update-nodejs-and-nodered)
  ```

- Installer questions

  - **Would you like to install the Pi-specific nodes?:** Yes

  - **Settings file:** use default (`/home/<username>/.node-red/settings.js`)

  - **Do you want to setup user security? :** Yes

    - **User permissions:** full access

    - **Add another user?:** No

  - **Do you want to enable the Projects feature? :** No

  - **Enter a name for your flows file:** use default (`flows.json`)

  - **Provide a passphrase to encrypt your credentials file:** leave empty (press Enter)

  - **Select a theme for the editor:** use default

  - **Select the text editor component to use in the Node-RED Editor:** use default (`monaco`);

  - **Allow Function nodes to load external modules? :** Yes

- Automatically start Node-RED on boot

  ```sh
  sudo systemctl enable nodered.service
  
  sudo systemctl start nodered.service
  ```

- Browse to `http://<rpi-ip-address>:1880`

### Node-RED concepts

- A flow-based development tool for visual programming (drag-and-drop) and deployment using a browser-based editor.

- Runtime and API running in Node.js environment.

- Components
  
  - **Nodes:** Performs some action on the data passing through the flow.

  - **Flows:** A set of connected nodes that perform a task when executed.

  - **Messages:** The data passed between nodes in a flow.

  - **Palette:** The library of available nodes that you can use in your flows.

  - **Workspace:** The area where you create and manage your flows.