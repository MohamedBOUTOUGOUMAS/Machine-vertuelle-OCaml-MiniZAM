let f x =
  let g y =
    let h z = z + 1
    in
    (h y) + 1
  in
  (g x) + 1
in
f 38
