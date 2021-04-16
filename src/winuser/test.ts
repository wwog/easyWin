import * as api from "./index";

//@ts-ignore
import native from "../../nwinuser.node"
let i = 0
let a = []
for (const item of Object.keys(native)) {
  //@ts-ignore
  if (api[item]) {
    
  } else {
    i++
    a.push(item)
  }
}

if (i == 0) {
  console.log('全部实现')
}
if (i > 0) {
  console.log('待实现方法:')
  console.log(a)
}