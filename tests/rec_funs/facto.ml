let rec facto x =
  if x = 0 then 1
  else x * facto (x-1)

let _ = facto 5
