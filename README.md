# Smart Lock System

This Arduino-based project implements a smart lock system that uses a 4x4 keypad, an I2C 1602 LCD, a servo motor, and a fingerprint sensor for security. The system allows you to lock and unlock a door using a password or a fingerprint scan.

## Features
- **Keypad Entry**: Enter a password using a 4x4 keypad to unlock the door.
- **Fingerprint Authentication**: Unlock the door with a fingerprint scan.
- **LCD Display**: Provides user feedback and instructions on a 1602 I2C LCD.
- **Servo Motor Control**: Opens and closes the door using a servo motor.
- **Secure Locking Mechanism**: Ensures the door remains securely locked when closed.

## Components Used
- Arduino Uno
- 4x4 Keypad
- 1602 I2C LCD
- Servo Motor
- Fingerprint Sensor
- Miscellaneous: Wires, Breadboard, Power Supply

## Installation
1. Clone the repository to your local machine.
    ```sh
    git clone https://github.com/yourusername/SmartLockSystem.git
    ```
2. Open the `SmartLockSystem.ino` file in the Arduino IDE.
3. Download app here https://kodular.app/DBU-DGJ
4. Connect the components as per the circuit diagram.
5. Upload the code to your Arduino board.

## Usage
- Enter the predefined password using the keypad to unlock the door.
- Use the fingerprint sensor to authenticate and unlock the door.
- The LCD will display relevant messages and status updates.
- Press `#` on the keypad to lock the door again.

## Customization
- Change the default password by modifying the `Specific` variable in the code.
- Adjust servo motor angles and timings as needed for your specific setup.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## Acknowledgments
- Special thanks to the open-source community for providing libraries and resources.

---

Feel free to reach out if you have any questions or need further assistance.
