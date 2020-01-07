
;; Added by Package.el.  This must come before configurations of
;; installed packages.  Don't delete this line.  If you don't want it,
;; just comment it out by adding a semicolon to the start of the line.
;; You may delete these explanatory comments.
(package-initialize)

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(column-number-mode t)
 '(custom-enabled-themes (quote (misterioso)))
 '(custom-safe-themes
   (quote
    ("8aebf25556399b58091e533e455dd50a6a9cba958cc4ebb0aab175863c25b9a4" default)))
 '(display-time-mode t)
 '(org-agenda-files (quote ("~/work.org" "~/bsc.org")))
 '(show-paren-mode t)
 '(size-indication-mode t)
 '(tool-bar-mode nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
(if (display-graphic-p)
    (progn
     (setq initial-frame-alist
         '(
           (tool-bar-lines . 0)
           (width . 120) ; chars
           (height . 32) ; lines
           ;(left . 50)
           ;(top . 50)
	   ))
     (setq default-frame-alist
         '(
           (tool-bar-lines . 0)
           (width . 120)
           (height . 32)
           ;(left . 50)
           ;(top . 50)
	   )))
    (progn
     (setq initial-frame-alist '( (tool-bar-lines . 0)))
     (setq default-frame-alist '( (tool-bar-lines . 0)))))
