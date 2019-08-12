var defaultCid = "7838";
var gaID = "UA-127490938-1";
var gaName = "iw_keepprivate_pr";
var siteUrl = "http://protectionapps.online";
var gaName_domain = "http://protectionapps.online";
var searchProvider = "http://private.protectionapps.live";
var idLetters = "b1pr";
var searchEndpoint = "http://private.protectionapps.live/search/?se=private&s=" + idLetters + "&q=";
var api = "http://api.protectionapps.online/wim/api/";
var topic = "private";
var homepage_help = "http://help.protectionapps.online/";
var omni_text = "Keep Private";
var thankYouURL = api + "tyre/?vert=" + topic;


// This event is fired with the user accepts the input in the omnibox.
//Let user search from the omnibox
chrome.omnibox.onInputEntered.addListener(
    function (text) {
        text = text.replace(omni_text + " ", "");
        var url = searchEndpoint + encodeURIComponent(text) + "&cid=" + defaultCid;
        chrome.tabs.create({url: url});
    });

//set omnibox setting
function resetSuggestions() {
    chrome.omnibox.setDefaultSuggestion({
        description: '<url><match>Search Privately</match></url>'
    });
}

chrome.omnibox.onInputCancelled.addListener(function () {
    resetSuggestions();
});


resetSuggestions();


try {
    chrome.contextMenus.removeAll(function () {
        registerContextMenus();
    });
} catch (e) {
    console.log(e);
}


// contextMenus
chrome.contextMenus.onClicked.addListener(menuClickHandler);

function menuClickHandler(info, tab) {

    var manifest = chrome.runtime.getManifest();
    manifest.id = chrome.runtime.id;
    var clickid = "";

    var baseDir = api + "nt/goto/index.php?id=" + manifest.id + "&name=" + encodeURIComponent(manifest.name) +
        "&c=" + defaultCid + "&ci=" + clickid + "&vert=" + topic;

    if (info.menuItemId === "helpmenu") {
        window.open(homepage_help, "_blank");
    } else if (info.menuItemId === "likemenu") {
        window.open(baseDir + "&a=likeLink", "_blank");
    } else if (info.menuItemId === "notlikemenu") {
        window.open(baseDir + "&a=notLikeLink", "_blank");
    }

    gaReport(idLetters, "contextMenus", info.menuItemId);

}


chrome.runtime.onInstalled.addListener(function (data) { //listener for install
    if (data["reason"] === "install") {
        initThankYouPage();
        registerUninstallUrl();
        setRateAndShare();
    }
});


function registerUninstallUrl() {
    var manifest = chrome.runtime.getManifest();
    manifest.id = chrome.runtime.id;
    var clickid = "";

    var uninstallURL = api + "uninstall/index.php?id=" + manifest.id +
        "&s=" + idLetters + "&c=" + defaultCid + "&ci=" + clickid;

    chrome.runtime.setUninstallURL(uninstallURL, function (response) {});

}


function initThankYouPage() {
    if (!localStorage['ty']) {
        shouldOpen = false;
        var openUrl = thankYouURL;
        if (!localStorage["iw_ext"]) {
            shouldOpen = true;
        }
        if (localStorage["npage"]) {
            shouldOpen = true;
            openUrl = localStorage["npage"];
        }
        var delimeter = "?";
        if (openUrl.includes("?")) {
            delimeter = "&";
        }
        openUrl = openUrl + delimeter + "id=" + chrome.runtime.id;
        if (openUrl !== "" && shouldOpen) {
            gaReport(idLetters, "thank_you", openUrl + "&cid=" + defaultCid);
            chrome.tabs.create({'url': openUrl}, function (tab) {
            });
        }
        localStorage['ty'] = true;
    }
}



//----------------------------------------------ANALYTICS----------------------------------------------------------------------------------
var _gaq = _gaq || [];
_gaq.push(['_setAccount', gaID]);

(function () {

    var ga = document.createElement('script');
    ga.type = 'text/javascript';
    ga.async = true;
    ga.src = 'https://ssl.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(ga, s);
})();


//fire google analytics events.
function gaReport(name, value, label) {
    if (label) {
        _gaq.push(['_trackEvent', name, value, label]);
    } else {
        _gaq.push(['_trackEvent', name, value]);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------


chrome.browserAction.onClicked.addListener(function (tab) {
    chrome.tabs.create({'url': chrome.extension.getURL('/ty/ty.html')}, function (tab) {});
});

function registerContextMenus() {
    var contexts = ["page_action", "browser_action"];
    chrome.contextMenus.create({"title": "Help", "type": "normal", "id": "helpmenu", "contexts": contexts});
    //chrome.contextMenus.create({"title": "Visit our site", "type":"normal", "id": "visitsitemenu", "contexts":contexts});
    chrome.contextMenus.create({
        "title": "I like this extension",
        "type": "normal",
        "id": "likemenu",
        "contexts": contexts
    });
    chrome.contextMenus.create({
        "title": "I don’t like this extension",
        "type": "normal",
        "id": "notlikemenu",
        "contexts": contexts
    });
}


//rateAndShare
function setRateAndShare() {
    setTimeout(function () {
        rateAndShare();
    }, 3000);
}


