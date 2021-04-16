//@ts-ignore
import api from '../../nfile.node';

/**
 * @function 资源管理器定位文件
 * @param hWnd 
 */
export function OpenFolderAndSelect(path: string) {
  //test:ok
  return api.OpenFolderAndSelect(path)
}



