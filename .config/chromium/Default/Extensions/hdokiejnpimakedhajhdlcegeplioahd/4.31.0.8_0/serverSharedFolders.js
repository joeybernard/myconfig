LPServer.sharing=LPServer.sharing||{},LPServer.sharing.folder=function(){var e="share.php",r="companyuser",a="Shared-",s=5e3,n=function(e,r){r.success(e,{sharedFolder:r.params.sharedFolder,shareInfo:r.params.shareInfo})},t=function(e,r,a){if(r.length>0){e.adminuidcnt=r.length;for(var s=0,n=r.length;s<n;++s){var t=r[s],d=new LPServer.ext.RSAKey;LPServer.ext.parsePublicKey(d,t.key),e["adminsharekey"+s]=d.encrypt(LPServer.ext.bin2hex(a)),e["adminuid"+s]=t.uid}}},d=(i=function(e){var r=[];if(e.groupname)for(var a=e.groupname.split(","),s=0,n=a.length;s<n;++s)r.push(a[s]);return r},o={nouser:function(e,r){r.error&&r.error(""),LPServer.callback(r,"invite",{emails:e.unknownusers.split(",")})},default:u=function(e,r){if(e.success){for(var a={},s=0;void 0!==e["pubkey"+s];)a[e["username"+s]]={uid:e["uid"+s],cgid:e["cgid"+s],pubkey:e["pubkey"+s]},++s;var n=i(e);n.length>0&&LPServer.callback(r,"emptyGroups",n),r.success(a)}else r.error()},emptygroup:u,noshareerr:function(e,r){r.error(LPServer.ext.translate("Sorry, company policy prohibits use of this feature."))}},function(r){LPServer.jsonRequest({url:e,data:{getpubkey:1,uid:"string"==typeof r.params.userInfo?r.params.userInfo:JSON.stringify(r.params.userInfo),jsonr:1},callbacks:o,userSupplied:r})}),i,u,o,l,p=(c=function(e,r){var a=new LPServer.ext.RSAKey;return LPServer.ext.parsePublicKey(a,r),a.encrypt(LPServer.ext.bin2hex(e))},m=function(e,r){for(var a in r){var s=r[a];if("group"===s.type&&e.cgid===s.uid)return a}return null},f=function(r,a){var s={id:a.params.shareInfo.id,update:1,add:1,sharename:a.params.shareInfo.sharename,name:a.params.shareInfo.name,readonly:a.params.readonly?1:0,give:a.params.hidePasswords?0:1,notify:a.params.notify?1:0,canadminister:a.params.can_administer?1:0,xmlr:1},n=a.params.newMembers?a.params.newMembers:{},t=0,d=0,i=[],u={};for(var o in r){var l=r[o];n[o]&&void 0!==n[o]||(n[o]={}),l.readOnly="object"==typeof n&&n[o].readOnly?1:s.readonly,l.canAdminister="object"==typeof n&&n[o].canAdminister?1:s.canadminister,l.give="object"!=typeof n||n[o].hidePasswords||void 0===n[o].hidePasswords?s.give:1,l.pubkey?(s["sharekey"+t]=c(a.params.shareInfo.key,l.pubkey),s["uid"+t]=l.uid,s["cgid"+t]=l.cgid,s["readonly"+t]=l.readOnly,s["canadminister"+t]=l.canAdminister,s["give"+t]=l.give,++t):(s["msfuser"+d]=l.uid,s["msfcgid"+d]=l.cgid,s["msfreadonly"+d]=l.readOnly,s["msfcanadminister"+d]=l.canAdminister,s["msfgive"+d]=l.give,i.push(o),++d),u[m(l,n)||o]=!0}var p=t+d;p>0?LPServer.xmlRequest({url:e,data:s,callbacks:{useradded:function(e,r){p<=6&&i.length>0&&LPServer.callback(r,"noSharingKeyUsers",i),r.success(LPServer.ext.translate("%1 users/groups were invited.",Object.keys(u).length),u)}},userSupplied:a}):a.error()},function(e){d(LPServer.extend({},e,{params:{userInfo:e.params.newMembers},success:function(r){f(r,e)}}))}),c,m,f,h=(S={ok:function(e,r){var a=LPServer.getAttr(e,"id");r.params.sharedFolder.aid=a,r.params.shareInfo.id=a,r.params.shareInfo.shareid=a,r.params.shareInfo.uid=LPServer.getAttr(e,"uid"),n(LPServer.ext.translate("Shared Folder %1 created.",r.params.sharedFolder.group),r)},exceededlimit:function(e,r){r.error(LPServer.ext.translate("Sorry, as a LastPass Premium user, you are limited to one Shared Folder. Please consider using LastPass Enterprise if you would like more."))},premiumrequired:function(e,r){r.error(LPServer.ext.translate("Sorry, LastPass Premium is required to create a Shared Family Folder"))},alreadyexists:function(e,r){r.error(LPServer.ext.translate("That group already exists."))}},v=function(r,n){var d=r[n.params.username].pubkey;if(d){var i=n.params.sharedFolder,u=n.params.shareInfo=n.params.shareInfo||{},o={id:0,update:1,newusername:n.params.username+"-"+i.group,name:0===i.group.indexOf(a)?i.group.substring(a.length):i.group,xmlr:1},l=LPServer.ext.makeRandomPassword(),p=u.key=LPServer.ext.makeKey(o.newusername,l,s);o.newhash=LPServer.ext.makeHash(p,l,s);var c=new LPServer.ext.RSAKey;LPServer.ext.parsePublicKey(c,d),o.sharekey=u.sharekey=c.encrypt(LPServer.ext.bin2hex(p)),o.sharename=u.sharename=LPServer.ext.encryptCBC(i.group,p),t(o,n.params.superusers,p),LPServer.xmlRequest({url:e,data:o,callbacks:S,userSupplied:n})}else LPServer.callback(n,"sharingkeyrequired"),n.error&&n.error("")},P=function(e,a){var s={};s[a.params.username]={uid:a.params.uid,type:r},a.params.superusers=e,d(LPServer.extend({},a,{params:{userInfo:s},success:function(e){v(e,a)}}))},function(e){LPServer.jsonRequest({url:"getSuperUserInfo.php",success:P,userSupplied:e})}),S,v,P,g=(L={ok:function(e,r){n(LPServer.ext.translate("Shared Folder %1 was renamed.",r.params.shareInfo.name),r)}},function(r){r.params.shareInfo.name=r.params.sharedFolder.group.substring(a.length),r.params.shareInfo.sharename=LPServer.ext.encryptCBC(r.params.sharedFolder.group,r.params.shareInfo.key),LPServer.xmlRequest({url:e,data:{update:1,rename:1,id:r.params.shareInfo.id,name:r.params.shareInfo.name,sharename:r.params.shareInfo.sharename,xmlr:1},callbacks:L,userSupplied:r})}),L,y=(x=function(e,r){r.params.shareInfo.deleted="1",n(LPServer.ext.translate("Shared Folder deleted."),r)},function(r){LPServer.xmlRequest({url:e,data:{id:r.params.shareInfo.id,delete:1,xmlr:1},callbacks:{deleted:x},userSupplied:r})}),x,b=(k=function(e,r){r.success(LPServer.ext.translate("Member removed."))},function(r){var a={id:r.params.shareid,xmlr:1};r.params.msfuser?(a.msfdelete=1,a.msfuser=r.params.uid):(a.update=1,a.delete=1,a.uid=r.params.uid),LPServer.xmlRequest({url:e,data:a,callbacks:{ok:k},userSupplied:r})}),k,I,R,w=(F=function(e,r){r.success(LPServer.ext.translate("Permissions saved."))},function(e){LPServer.xmlRequest({url:"editSharedFolderUsers.php",data:{cmd:"edit",xml:1,shareid:e.params.shareInfo.id,request:JSON.stringify(e.params.updatedPermissions)},callbacks:{ok:F},userSupplied:e})}),F,q=function(r,a,s){var n={id:a.params.shareInfo.id,xmlr:1};n[r]=1,LPServer.xmlRequest({url:e,data:n,callbacks:s,userSupplied:a})},j=(A=function(e,r){r.params.shareInfo.download="1",n(LPServer.ext.translate("Shared Folder will now be downloaded."),r)},function(e){q("startdownloading",e,{ok:A})}),A,M=(K=function(e,r){r.params.shareInfo.download="0",n(LPServer.ext.translate("Shared Folder will no longer be downloaded."),r)},function(e){q("stopdownloading",e,{ok:K})}),K,O=(E={undeleted:function(e,r){r.params.shareInfo.deleted="0",n(LPServer.ext.translate("Shared Folder restored."),r)}},function(r){LPServer.xmlRequest({url:e,data:{id:r.params.shareInfo.id,undelete:1,xmlr:1},callbacks:E,userSupplied:r})}),E,D=(_={purged:function(e,r){r.success(LPServer.ext.translate("Shared Folder purged."))}},function(r){LPServer.xmlRequest({url:e,data:{id:r.params.shareInfo.id,purge:1,xmlr:1},callbacks:_,userSupplied:r})}),_,C=(U=function(e,r){r.success(e.folders)},function(e){LPServer.jsonRequest({url:"getSharedFolderInfo.php",success:U,userSupplied:e})}),U,N=(B={success:function(e,r){r.params.shareInfo.accepted="1",n(LPServer.ext.translate("Shared Folder accepted."),r)}},function(r){LPServer.jsonRequest({url:e,data:{folder:r.params.shareInfo.id,acceptfolder:1,jsonr:1},callbacks:B,userSupplied:r})}),B,H=(J={success:function(e,r){r.success(LPServer.ext.translate("Shared Folder rejected."))}},function(r){LPServer.jsonRequest({url:e,data:{id:r.params.shareInfo.id,rejectfolder:1,jsonr:1},callbacks:J,userSupplied:r})}),J,T=(G={success:function(e,r){r.success(LPServer.ext.translate("Shared Folder member reinvited."))}},function(r){var a={reinvite:1,invitee:r.params.uid,folder:r.params.shareid,jsonr:1};"1"===r.params.ent&&(a.ent="on"),LPServer.jsonRequest({url:e,data:a,callbacks:G,userSupplied:r})}),G,X=(Y={success:function(e,r){r.params.shareInfo.cid=LPServer.getAttr(e,"cid"),r.params.shareInfo.outside_enterprise=LPServer.getAttr(e,"outside_enterprise"),n(LPServer.ext.translate("Personal Shared Folder moved into Enterprise. You can now adminster the folder."),r)}},z=function(r,a){var s={id:a.params.shareInfo.id,moveintoenterprise:1,xmlr:1};t(s,r,a.params.shareInfo.key),LPServer.xmlRequest({url:e,data:s,callbacks:Y,userSupplied:a})},function(e){LPServer.jsonRequest({url:"getSuperUserInfo.php",success:z,userSupplied:e})}),Y,z;return{SHARED_FOLDER_NAME_PREFIX:a,getFolders:C,getPublicKeys:d,create:h,rename:g,remove:y,accept:N,reject:H,addMembers:p,getMembers:function(e){LPServer.jsonRequest({url:"getSharedFolderMembers.php",data:{shareid:e.params.shareid},userSupplied:e})},removeMember:b,reinviteMember:T,updateMemberPermissions:w,getRestrictions:function(e){LPServer.jsonRequest({url:"getSharedFolderRestrictions.php",data:e.params,userSupplied:e})},updateRestrictions:function(r){LPServer.textRequest({url:e,data:{id:r.params.shareid,edit:1,limit:1,aids:r.params.aids,numaids:r.params.aids.length>0?r.params.aids.split(",").length:0,additionaluids:r.params.additionaluids,hidebydefault:r.params.hidebydefault?1:0,uid:r.params.uid,xmlr:1},success:function(){r.success(LPServer.ext.translate("Access restrictions updated."))},userSupplied:r})},startDownloading:j,stopDownloading:M,restoreDeleted:O,purgeDeleted:D,convertToEnterprise:X}}();
//# sourceMappingURL=sourcemaps/serverSharedFolders.js.map