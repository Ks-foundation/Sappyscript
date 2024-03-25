// Saplectron.js

const { app, BrowserWindow } = require('electron');
const fs = require('fs');
const path = require('path');

class SaplectronWindow {
    constructor(options) {
        this.window = new BrowserWindow(options);
    }

    loadURL(url) {
        this.window.loadURL(url);
    }

    on(event, callback) {
        this.window.on(event, callback);
    }

    show() {
        this.window.show();
    }

    html(filePath) {
        const htmlContent = fs.readFileSync(filePath, 'utf8');
        this.window.loadURL(`data:text/html;charset=utf-8,${encodeURIComponent(htmlContent)}`);
    }

    js(filePath) {
        const jsContent = fs.readFileSync(filePath, 'utf8');
        this.window.webContents.executeJavaScript(jsContent);
    }

    css(filePath) {
        const cssContent = fs.readFileSync(filePath, 'utf8');
        this.window.webContents.insertCSS(cssContent);
    }
}

module.exports = {
    SaplectronWindow
};
