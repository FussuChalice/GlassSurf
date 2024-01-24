// content.js

const DEFAULT_PORT = 3040;

const GLASS_SURF_SERVER_STATE_URL = `http://localhost:${DEFAULT_PORT}/state/`;
const GLASS_SURF_SERVER_BG_URL = `http://localhost:${DEFAULT_PORT}/bg/`;

const GLASS_SURF_SERVER_LOAD_INTERVAL = 100;

const body = document.body;
body.style.backgroundAttachment = "fixed";

let tmp_background_image_url;

function updateBackground() {
  fetch(GLASS_SURF_SERVER_STATE_URL, {
    method: 'GET',
  })
    .then((response) => {
      if (!response.ok) {
        throw new Error(`HTTP error! Status: ${response.status}`);
      }
      return response.text();
    })
    .then((state) => {
      if (state === "1") {
        if (tmp_background_image_url) {
          URL.revokeObjectURL(tmp_background_image_url);
        }

        fetch(GLASS_SURF_SERVER_BG_URL)
          .then((response) => response.blob())
          .then((blob) => {
            tmp_background_image_url = URL.createObjectURL(blob);

            var img = new Image();
            img.onload = function () {
              body.style.backgroundImage = "url(" + tmp_background_image_url + ")";
            };
            img.src = tmp_background_image_url;
          })
          .catch((error) => {
            console.error("Error fetching background image:", error);
          });
      }
    })
    .catch((error) => {
      console.error("Error checking server state:", error);
    });
}

function clearConsole() {
  console.clear();
}

let loadBackgroundImageInterval = setInterval(updateBackground, GLASS_SURF_SERVER_LOAD_INTERVAL);
let clearConsoleInterval = setInterval(clearConsole, 1000 * 3600);

function appendStyleToBody(styleContent) {
  // Create a new style element
  var styleElement = document.createElement('style');
  // Set the style content
  styleElement.innerHTML = styleContent;
  // Append the style element to the document body
  document.body.appendChild(styleElement);
}

// // Styles
appendStyleToBody(`
body > div.L3eUgb > div.o3j99.ikrT4e.om7nvf > form > div:nth-child(1) > div.A8SBwf > div.RNNXgb {background-color: transparent !important;}
#gb {background-color: transparent !important;}
body > div.L3eUgb > div.o3j99.c93Gbe {background-color: transparent !important;}
body > div.L3eUgb > div.o3j99.c93Gbe > div.uU7dJb {border: none !important;}
#searchform > div.sfbg {background-color: transparent !important;}
#appbar {background-color: transparent !important;}
.rsGxI.Ww4FFb, .Ww4FFb {background-color: transparent !important;}
.RNNXgb, .GKS7s {background-color: transparent !important;}
.F9Idpe {background: transparent !important}
`);
