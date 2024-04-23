document.addEventListener("DOMContentLoaded", event => {
    const app = firebase.app();
    console.log(app)
});

function googleLogin() {
// Using a popup.
var provider = new firebase.auth.GoogleAuthProvider();
provider.addScope('profile');
provider.addScope('email');
firebase.auth().signInWithPopup(provider).then(function(result) {
 // This gives you a Google Access Token.
var token = result.credential.accessToken;
// The signed-in user info.
 var user = result.user;
document.write(`<h1>Hello ${user.displayName}</h1>`);
document.write(`<p>This interface will turn on and off LEDs on local Arduino MKR WiFi 1010</p>`);
console.log(user)


const button_red = document.createElement('button')
button_red.innerText = 'RED LED OFF'
button_red.id = 'red_led_button'

button_red.addEventListener('click',() => {
if (button_red.innerText == 'RED LED OFF'){
    button_red.innerText = 'RED LED ON'
    button_blue.innerText = 'BLUE LED OFF'
    button_green.innerText = 'GREEN LED OFF'
    turnOnREDLED()
    turnOffGreenLED()
    turnOffBlueLED()
}
})

const button_blue = document.createElement('button')
button_blue.innerText = 'BLUE LED OFF'
button_blue.id = 'blue_led_button'

button_blue.addEventListener('click',() => {
if (button_blue.innerText == 'BLUE LED OFF'){
    button_blue.innerText = 'BLUE LED ON'
    button_green.innerText = 'GREEN LED OFF'
    button_red.innerText = 'RED LED OFF'
    turnOnBlueLED()
    turnOffREDLED()
    turnOffGreenLED()
}
})

const button_green = document.createElement('button')
button_green.innerText = 'GREEN LED OFF'
button_green.id = 'green_led_button'

button_green.addEventListener('click',() => {
if (button_green.innerText == 'GREEN LED OFF'){ 
    button_green.innerText = 'GREEN LED ON'
    button_blue.innerText = 'BLUE LED OFF'
    button_red.innerText = 'RED LED OFF'
    turnOnGreenLED()
    turnOffREDLED()
    turnOffBlueLED()
}

})

const database = firebase.database();

// Function to turn on the LED
function turnOnREDLED() {
  // Set the value in the database to turn on the LED
  database.ref('LED').set('red', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned on successfully');
    }
  })
  database.ref('LED_RED').set('On', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned on successfully');
    }
  })
}

function turnOffREDLED() {
  // Set the value in the database to turn on the LED
  database.ref('LED_RED').set('Off', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned off successfully');
    }
  })
}
  
// Function to turn on the LED
function turnOnBlueLED() {
  // Set the value in the database to turn on the LED
  database.ref('LED').set('blue', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned on successfully');
    }
  })
  database.ref('LED_BLUE').set('On', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned on successfully');
    }
  })
}

function turnOffBlueLED() {
  // Set the value in the database to turn on the LED
  database.ref('LED_BLUE').set('Off', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned off successfully');
    }
  })
}

// Function to turn on the LED
function turnOnGreenLED() {
  // Set the value in the database to turn on the LED
  database.ref('LED').set('green', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned on successfully');
    }
  })
  database.ref('LED_GREEN').set('On', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned on successfully');
    }
  })
}

function turnOffGreenLED() {
  // Set the value in the database to turn on the LED
  database.ref('LED_GREEN').set('Off', (error) => {
    if (error) {
      console.error('Error turning on LED:', error);
    } else {
      console.log('LED turned off successfully');
    }
  })
}



    document.write('<P></P>')
    document.body.appendChild(button_red)
    document.write('<P></P>')
    document.body.appendChild(button_blue)
    document.write('<P></P>')
    document.body.appendChild(button_green)
    document.write('<P></P>')

    

})

}
