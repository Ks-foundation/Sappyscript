// main.sps

import "saplectron";

log("Creating Saplectron window...");
let mainWindow = new SaplectronWindow({
    width: 800,
    height: 600
});

log("Loading HTML...");
mainWindow.html("index.html");

log("Loading JavaScript...");
mainWindow.js("script.js");

log("Loading CSS...");
mainWindow.css("styles.css");

log("Showing window...");
mainWindow.show();
