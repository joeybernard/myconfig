var processAcctsIframeMessage=function(e){"getdata"===e.data.msg?bg.processCS(null,{cmd:"ipcgetdata",url:e.data.url,callback:function(t){"ipcgotdata"===t.cmd&&e.source.postMessage(t,e.origin)}},null):"closeiframe"===e.data.msg?bg.closeSettingsIframe():"refreshsites"===e.data.msg?bg.refreshsites():"storeaccountlinktoken"===e.data.msg?"function"==typeof bg.storeAccountLinkToken&&bg.storeAccountLinkToken(e.data.payload):"websiteevent"==e.data.msg&&(g_websiteeventtarget=e,document.getElementById("eventtype").value=e.data.eventtype,document.getElementById("eventdata1").value=e.data.eventdata1,document.getElementById("eventdata2").value=e.data.eventdata2,document.getElementById("eventdata3").value=e.data.eventdata3,document.getElementById("eventdata4").value=e.data.eventdata4,document.getElementById("eventdata5").value=e.data.eventdata5,website_event())};
//# sourceMappingURL=sourcemaps/acctsiframe.js.map