

let f x = (fun y -> x + y)

let g x = f (1+x)

let _ = g 3 4
