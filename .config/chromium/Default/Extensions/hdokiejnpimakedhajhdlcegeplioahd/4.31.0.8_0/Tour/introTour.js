var IntroTour=function(e,t,r,n,o,s){"use strict";var u,i;function c(){i.laterThisTour(),s.save(i.getOptions())}function a(){i.neverThisTour(),s.save(i.getOptions())}function T(){i.takeThisTour(),s.save(i.getOptions())}function l(){s.save(null)}function b(){i.makeLaterNowTours(),s.save(i.getOptions())}function v(){u&&(u.closeCurrentStep(),u.unSubscribeAction("later"),u.unSubscribeAction("never"),u.unSubscribeAction("start"),u.unSubscribeAction("close"),u.cleanup(),u=null)}function A(e){o.get(o.CLEAR_DATA).subscribeFirst(function(){e&&e.cleanup&&e.cleanup()})}function f(r,n){var l=this,b;v(),s.migrateOldPrefs(),r?(b=(i=new e).getAvailableTour(r))&&(u=new t(b),A(l),u.startFlow(r),n&&T()):(i=new e(s.retrieve()),s.save(i.getOptions()),(b=i.getAvailableTour())?((u=new t(b)).subscribeToAction("later",c),u.subscribeToAction("never",a),u.subscribeToAction("start",T),u.subscribeToAction("close",v),A(l),u.startFlow(r)):o.get(o.INTRO_TOURS_LOADED).publish())}return{start:f,cleanup:v,neverThisTour:a,laterThisTour:c,takeThisTour:T,resetAllTours:l,makeLaterNowTours:b}}(IntroTourQueue,IntroTourFlow,IntroTourData,LPProxy,Topics,IntroTourPreferences);
//# sourceMappingURL=sourcemaps/Tour/introTour.js.map