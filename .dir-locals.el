;;; Directory Local Variables
;;; For more information see (info "(emacs) Directory Variables")
((c++-mode .
           ((flycheck-gcc-language-standard . "c++14")
            (flycheck-clang-language-standard . "c++14")))
 (c-c++ .
        ((c-c++-enable-clang-support . t)
         (c-c++-default-mode-for-headers . "c++-mode")))
 )
