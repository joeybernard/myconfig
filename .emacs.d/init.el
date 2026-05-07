;; Start by quieting unnecessary noise
(setq inhibit-startup-message t)
(setq initial-scratch-message nil)
(defun display-startup-echo-area-message()
  (message ""))


;; Am I on the dev box?
(defvar ccdbdev-p (or (equal (system-name) "ccdbdev-ng") (equal (system-name) "ccdbdev-ng.driirn.ca")))

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


;; Setup personal info
(setq user-full-name "Joey Bernard"
      user-mail-address "druid.bernard@gmail.com")


;; Set line numbers
(setq display-line-numbers-type t)



;; Setup a spot for local elisp code
(defvar local-lisp "~/.emacs.d/local-lisp/")
(add-to-list 'load-path  local-lisp)
(let ((default-directory local-lisp))
  (normal-top-level-add-subdirs-to-load-path))



;; Set the theme
(use-package tron-legacy-theme
  :config
  (load-theme 'tron-legacy t))



;; Autocomplete stuff
(with-eval-after-load 'company
  (define-key company-mode-map (kbd "<tab>") 'company-indent-or-complete-common))
(use-package company)
(use-package company-posframe 
   :init (company-posframe-mode 1))



;; Setup org-mode stuff
(use-package org)

;; include diary data
(setq org-agenda-include-diary t)

;; Must do this so the agenda knows where to look for my files
(setq org-agenda-files '("~/my_org"))

;; When a TODO is set to a done state, record a timestamp
(setq org-log-done 'time)

;; Startup unfolded
(setq org-startup-folded nil)

;; Jump to open clock
(keymap-global-set "C-c j" 'org-clock-goto)

;; Default inbox
(setq org-default-notes-file "~/my_org/inbox.org")

;; Follow the links
(setq org-return-follows-link  t)

;; Inline images
(setq org-display-inline-images t)
(setq org-redisplay-inline-images t)
(setq org-startup-with-inline-images "inlineimages")

;; Associate all org files with org mode
(add-to-list 'auto-mode-alist '("\\.org\\'" . org-mode))

;; Make the indentation look nicer
(add-hook 'org-mode-hook 'org-indent-mode)

;; Remap the change priority keys to use the UP or DOWN key
(define-key org-mode-map (kbd "C-c <up>") 'org-priority-up)
(define-key org-mode-map (kbd "C-c <down>") 'org-priority-down)

;; Shortcuts for storing links, viewing the agenda, and starting a capture
(define-key global-map "\C-cl" 'org-store-link)
(define-key global-map "\C-ca" 'org-agenda)
(define-key global-map "\C-cc" 'org-capture)

;; When you want to change the level of an org item, use SMR
(define-key org-mode-map (kbd "C-c C-g C-r") 'org-shiftmetaright)

;; Hide the markers so you just see bold text as BOLD-TEXT and not *BOLD-TEXT*
(setq org-hide-emphasis-markers t)

;; Wrap the lines in org mode so that things are easier to read
(add-hook 'org-mode-hook 'visual-line-mode)

;; Setup org capture templates
(setq org-capture-templates
      '(;; other entries
        ("c" "Item to Current Clocked Task" item
         (clock)
         "%i%?" :empty-lines 1)
        ("t" "Todo" entry (file "~/my_org/todo.org")
         "* TODO %^{Task}\n:PROPERTIES:\n:CREATED: %U\n:END:\n%a\n"
          :prepend t)
        ("n" "Note" entry
         (file "~/my_org/inbox.org")
         "* %^{Note}\n:PROPERTIES:\n:CREATED: %U\n:END:\n"
         :prepend t)
        ("j" "Journal entry" plain
         (file+datetree+prompt "~/my_org/journal.org")
         "%K - %a\n%i\n%?\n")
        ;; other entries
        ))

;; Setup org todo keywords
(setq org-todo-keywords
      '((sequence
         "STARTED(s)"
         "TODO(t)"  ; next action
         "TOBLOG(b)"
         "WAITING(w@/!)"
         "READY(r)"
         "SOMEDAY(.)" "BLOCKED(k@/!)" "|" "DONE(x!)" "CANCELLED(c)")
        (sequence "PROJECT" "|" "DONE(x)")
        (sequence "LEARN" "TRY" "TEACH" "|" "COMPLETE(x)")
        (sequence "TOSKETCH" "SKETCHED" "|" "POSTED")
        (sequence "TOBUY" "TOSHRINK" "TOCUT"  "TOSEW" "|" "DONE(x)")
        (sequence "TODELEGATE(-)" "DELEGATED(d)" "|" "COMPLETE(x)")))

;; Setup org babel
(org-babel-do-load-languages 'org-babel-load-languages
   '((python . t)
     (octave . t)
     (C . t)
     (shell . t)))
(setq org-src-fontify-natively t)
(setq org-confirm-babel-evaluate nil)
(add-hook 'org-babel-after-execute-hook 'org-display-inline-images 'append)
(setq org-edit-src-content-indentation 0)

;;(use-package org-ics-import
;;	:load-path "~/.emacs.d/local-lisp/org-ics-import/")

;;(setq org-ics-import-update-interval 3600)
;;(setq org-ics-import-calendars-alist '(
;;   ("https://calendar.google.com/calendar/ical/druid.bernard%40gmail.com/private-6fe0c18dc92c51f1c6646fc3f7c94203/basic.ics" . "~/my_org/gcal.org")
;;   ("https://outlook.office365.com/owa/calendar/76529b53d3d64efd956dd377958fc5c8@alliancecan.ca/71a27ea4de514fdeb68426dea03a501411738982182761455362/calendar.ics" . "~/my_org/drac_outlook.org")
;;   ("https://outlook.office365.com/owa/calendar/ef9e8bf4c2f64d4faa08a7d828f99e84@unb.ca/cde34430e78d418b90b14926e4fed07e4299525889863396979/calendar.ics" . "~/my_org/unb.org")
;;   ("https://calendar.google.com/calendar/ical/joey.bernard%40gw.alliancecan.ca/private-544e253b15a3b76b3dbf9dd75081ae98/basic.ics" . "~/my_org/drac_gcal.org")
;;   )
;;)
;;(setq org-ics-import-exclude-strings '("Cancelled"))
;;(setq org-ics-import-confirmed-overwrite
;;   '("~/my_org/drac_gcal.org" "~/my_org/unb.org" "~/my_org/drac_outlook.org"
;;     "~/my_org/gcal.org"))

(use-package org-roam
  :ensure t
  :init
  (setq org-roam-v2-ack t)
  :custom
  (org-roam-directory "~/RoamNotes")
  :bind (("C-c n l" . org-roam-buffer-toggle)
         ("C-c n f" . org-roam-node-find)
         ("C-c n i" . org-roam-node-insert))
  :config
  (org-roam-setup))



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
(when (string= (system-name) ccdbdev-p)
  (with-eval-after-load 'eglot
    (add-to-list 'eglot-server-programs
		 '(ruby-mode . ("/home/bernardj/ccdb/ccdb_portal/vendor/bundle/ruby/3.2.0/bin/solargraph" "stdio")))))


;; Ruby setup
(use-package rinari)
(use-package bundler)
(use-package robe
   :hook
   ((ruby-mode-hook . robe-mode)
    (robe-mode-hook . ac-robe-setup)
    (ruby-mode-hook . auto-complete-mode)))
(use-package rspec-mode
   :config
   (progn
      (setq rspec-command-options "--fail-fast --format documentation")
      (keymap-set rspec-mode-map "C-c , ," 'rspec-rerun)))


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
