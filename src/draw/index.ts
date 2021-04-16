//@ts-ignore
import api from "../../ndraw.node";

/**
 * 画边框
 * color:0-255.
 * flash:闪动
 */
export function drawBorder(hWnd: number, { width = 3, color = 255, flash = false } = {}): void {
  api.drawBorder(hWnd, width, color, flash)
}

/* for(let i = 0;i<10;i++){
  drawBorder(788134,{flash:true})
} */
/**
 * 图标句柄以png编码保存到文件
 * @param hIcon 
 * @param filePath 
 */
export function hIconSave(hIcon: number, filePath: string): boolean {
  if (filePath.endsWith('png')) {
    throw new Error(`It should be saved as a PNG file`)
  }
  return api.HIconSave(hIcon, filePath)
}

/**
 * 图标句柄以png编码,从内存中取出Buffer
 * @param hIcon 图标句柄
 */
export function hIconToBuffer(hIcon: number) {
  let arr = api.HIconToBuffer(hIcon) as number[]
  return Uint8Array.from(arr)
}



