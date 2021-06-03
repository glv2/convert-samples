(use-modules (gnu packages autotools)
             (guix build-system gnu)
             ((guix licenses) #:prefix license:)
             (guix packages))

(define convert-samples
  (package
    (name "convert-samples")
    (version "1.0.0")
    (source #f)
    (build-system gnu-build-system)
    (native-inputs
     `(("autoconf" ,autoconf)
       ("automake" ,automake)))
    (synopsis "Program to convert samples between different formats")
    (description
     "@code{convert-samples} is a command-line program to convert samples
received from software defined radios from one format to another.")
    (home-page #f)
    (license license:gpl3+)))

convert-samples
