
(cl:in-package :asdf)

(defsystem "pick_ball_mbot_msgs-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "PathPlanning" :depends-on ("_package_PathPlanning"))
    (:file "_package_PathPlanning" :depends-on ("_package"))
    (:file "void_obstacle" :depends-on ("_package_void_obstacle"))
    (:file "_package_void_obstacle" :depends-on ("_package"))
  ))