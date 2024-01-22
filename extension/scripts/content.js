// content.js
// -----------------------------------------------------
// Copyright 2024 The GlassSurf Authors
// Use of this source code is governed by a MIT-style license that can be
// found in the LICENSE file.

const DEFAULT_PORT = 3040;

const body = document.body;
body.style.backgroundAttachment = "fixed";

fetch(`http://localhost:${DEFAULT_PORT}/bg/`, {
    method: "GET",
    }).then(response => response)
    .then(data => {
        console.log("GlassSurf server is up!!");

        function updateBackground() {
            var xhr = new XMLHttpRequest();
            xhr.responseType = 'arraybuffer';

            xhr.onreadystatechange = function() {
                if (xhr.readyState === 4 && xhr.status === 200) {
                    var imageBlob = new Blob([xhr.response], { type: 'image/png' });
                    var imageUrl = URL.createObjectURL(imageBlob);
                    var img = new Image();
                    img.onload = function() {
                        body.style.backgroundImage = 'url(' + imageUrl + ')';
                    };
                    img.src = imageUrl;
                }
            };
            xhr.open('GET', `http://localhost:${DEFAULT_PORT}/bg/`, true);
            xhr.send();
        }

        interval = setInterval(updateBackground, 10);

    })
    .catch((error) => {
      console.error('Error:', error);
      console.log("GlassSurf server is down!!");  
    });


// Custom themes of transparent for websites

if (window.location.href == "https://www.google.com/") {
  elems = [
    document.querySelector("#gb"),
    document.querySelector("body > div.L3eUgb > div.o3j99.ikrT4e.om7nvf > form > div:nth-child(1) > div.A8SBwf > div.RNNXgb"),
    document.querySelector("body > div.L3eUgb > div.o3j99.c93Gbe")
  ]

  elems.forEach(element => {
    element.style.backgroundColor = "transparent";
  });

  document.querySelector("body > div.L3eUgb > div.o3j99.c93Gbe > div.uU7dJb").style.border = "none";
}
