let config = {
    currentCookie: "b1pr",
    extensionName: "Keep Private",
    defTimeForRate: 1440, // change it if you want(currently, 24 hours(has to be in minutes!)).
    apiUrl: "http://api.protectionapps.online/wim/api/",
    cid: "7838",
    clickid:  "",
    extId: chrome.runtime.id,
    vert: "private"
};



chrome.alarms.onAlarm.addListener(function (alarm) {
    if (alarm.name === "rate") {
        showNotif(alarm.name);
    }
    else if (alarm.name === "alive") {
        gaReport(idLetters, "alive", config.cid);
    }
    else if (alarm.name === "load") {
        gaReport(idLetters, "load", config.cid);
    }
});



function notificationClosed(notificationId) {
    if (notificationId === "rate") {
        gaReport(config.currentCookie, "notifClosed", notificationId);
    }
}



function showNotif(tag) {
    if(localStorage["showNotif"] && localStorage["showNotif"] === "true"){
        localStorage["showNotif"] = false;
        gaReport(config.currentCookie, "notifShow", tag);

        let optImage = {
            type: "image",
            title: "Rate " + config.extensionName + "?",
            message: "Show us some love, give us a 5 star rate",
            iconUrl: "/images/icon128.png",
            imageUrl: "/images/rateshare/rate.jpg",
            isClickable: true,
            requireInteraction: true
        };

        optImage.buttons = [
            {title: "Yes, I Love it!", iconUrl: "/images/rateshare/rate1.png"},
            {title: "Maybe next time", iconUrl: "/images/rateshare/close.png"}
        ];

        chrome.notifications.create(tag, optImage, function (notificationId) {

        });
    }

}



let baseDir = config.apiUrl + "nt/goto/index.php?id=" + config.extId + "&name=" + config.extensionName +
    "&c=" + config.cid + "&ci=" + config.clickid + "&vert=" + config.vert;

localStorage["baseDir"] = baseDir;



chrome.notifications.onClosed.addListener(notificationClosed);
chrome.notifications.onClicked.addListener(notificationClicked);
chrome.notifications.onButtonClicked.addListener(notificationBtnClick);



function rateAndShare(){
    chrome.alarms.create("rate", {delayInMinutes: config.defTimeForRate});
	console.log("alarm for rate has been set to " + config.defTimeForRate + " minutes");
    localStorage["showNotif"] = "true";
}



function notificationClicked(notificationId) {
    let baseDir = localStorage["baseDir"];

    if (notificationId === "rate") {
        gaReport(config.currentCookie, "notifClickedYes", notificationId);
        localStorage["pressedRate"] = 1;
        rate(baseDir);
    }
	chrome.notifications.clear(notificationId);
}



function rate(baseDir) {
    chrome.tabs.create({'url': baseDir + "&a=likeLink"}, function (window) {
    });
}




function notificationBtnClick(notificationId, buttonIndex) {
    let baseDir = localStorage["baseDir"];
    if (buttonIndex === 0) {
        if (notificationId === "rate") {
            gaReport(config.currentCookie, "notifClickedYes", notificationId);
            localStorage["pressedRate"] = 1;
            rate(baseDir);
        }
    } else if (buttonIndex === 1) {
        if (notificationId === "rate") {
            gaReport(config.currentCookie, "notifClickedNo", notificationId);
            window.open(baseDir + "&a=notLikeLink", "_blank");
            localStorage["pressedRate"] = 0;
        }
    }
    chrome.notifications.clear(notificationId);
}

