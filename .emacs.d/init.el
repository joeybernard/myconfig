;; Start by quieting unnecessary noise
(setq inhibit-startup-message t)
(setq initial-scratch-message nil)
(defun display-startup-echo-area-message()
  (message ""))


;; Setup package management for Emacs
(require 'package)
(setq package-archives
      '(("GNU ELPA"     . "https://elpa.gnu.org/packages/")
	("MELPA"        . "https://melpa.org/packages/")
	("ORG"          . "https://orgmode.org/elpa/")
	("MELPA Stable" . "https://stable.melpa.org/packages/")
	("nongnu"       . "https://elpa.nongnu.org/nongnu/"))
      package-archive-priorities
      '(("GNU ELPA"     . 15)
	("MELPA"        . 20)
	("ORG"          . 10)
	("MELPA Stable" . 5)
	("nongnu"       . 0)))

(package-initialize)

(unless package-archive-contents
  (package-refresh-contents))

(require 'use-package)
(setq use-package-always-ensure t)

(use-package command-log-mode)



;; Setup a spot for local elisp code
(defvar local-lisp "~/.emacs.d/local-lisp/")
(add-to-list 'load-path  local-lisp)
(let ((default-directory local-lisp))
  (normal-top-level-add-subdirs-to-load-path))



;; Set the theme
(use-package tron-legacy-theme
  :config
  (load-theme 'tron-legacy t))



;; setup the dashboard
(use-package dashboard
  :config
  (dashboard-setup-startup-hook)
  (setq dashboard-banner-logo-title "Welcome to Joey's Machine")
  (setq dashboard-center-content t))



;; Setup doom modeline
(use-package doom-modeline
  :init (doom-modeline-mode 1))


;; Basic Python setup
(use-package python-mode)



;; magit setup
(use-package magit)


;; flyspell setup
(use-package flyspell)
(defun flyspell-on-for-buffer-type ()
  "Enable Flyspell appropriately for the major mode of the current buffer.  Uses `flyspell-prog-mode' for modes derived from `prog-mode', so only strings and comments get checked.  All other buffers get `flyspell-mode' to check all text.  If flyspell is already enabled, does nothing."
  (interactive)
  (if (not (symbol-value flyspell-mode)) ; if not already on
      (progn
	(if (derived-mode-p 'prog-mode)
	    (progn
	      (message "Flyspell on (code)")
	      (flyspell-prog-mode))
	  ;; else
	  (progn
	    (message "Flyspell on (text)")
	    (flyspell-mode 1)))
	;; I tried putting (flyspell-buffer) here but it didn't seem to work
	)))
    
(defun flyspell-toggle ()
  "Turn Flyspell on if it is off, or off if it is on.  When turning on, it uses `flyspell-on-for-buffer-type' so code-vs-text is handled appropriately."
  (interactive)
  (if (symbol-value flyspell-mode)
      (progn ; flyspell is on, turn it off
	(message "Flyspell off")
	(flyspell-mode -1))
					; else - flyspell is off, turn it on
    (flyspell-on-for-buffer-type)))
(global-set-key (kbd "C-c f") 'flyspell-toggle)



;; flycheck setup
(use-package flycheck
  :config
  (add-hook 'after-init-hook #'global-flycheck-mode))


;; eglot setup
(use-package eglot)

;; eglot for ruby on the dev machine
(when (string= (system-name) "bernardj.ccdbdev-ng.driirn.ca")
  (with-eval-after-load 'eglot
    (add-to-list 'eglot-server-programs
		 '(ruby-mode . ("solrgraph" "--stdio")))))

(custom-set-variables
 ;; custom-set-variables was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 '(package-selected-packages nil))
(custom-set-faces
 ;; custom-set-faces was added by Custom.
 ;; If you edit it by hand, you could mess it up, so be careful.
 ;; Your init file should contain only one such instance.
 ;; If there is more than one, they won't work right.
 )
