
const { copyFileSync, readdirSync, rmSync, existsSync } = require('fs')
const { join } = require('path')

let destDir = join(__dirname, '../')
let srcDir = join(__dirname, '../build/Release/')
let files = readdirSync(srcDir)
for (const file of files) {
  //如果用户编译不了也还有一份打包后使用
  if (file.endsWith('.node')) {
    let destFilePath = join(destDir, file)
    if (existsSync(destFilePath)) {
      rmSync(destFilePath)
    }
    copyFileSync(join(srcDir, file), destFilePath)
  }
}

