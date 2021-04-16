//@ts-ignore
import api from "../../nprocess.node"


export interface processInfo {
  ExeFile: string
  ParentId: number
  Id: number
  cntThreads: number
  pcPriClassBase: number
  [index: string]: string | number
}
//--------------原生大写开头
/**
 * 进程ID取运行路径
 * @param ProcessId 进程id
 */
export function QueryFullProcessImageName(ProcessId: number): string {
  //test:ok
  return api.QueryFullProcessImageName(ProcessId);
}

/**
 * 系统盘符转换为DOS设备描述
 * @param Drive 盘符,例如:C,D
 */
export function DriveToDosDevice(Drive: string): string {
  //test:ok
  return api.DriveToDosDevice(Drive);
}

/**
 * 获取所有盘符
 */
export function GetDrives(): string[] {
  //test:ok
  let arr = api.GetDrives() as number[]
  return arr.map((v) => {
    return String.fromCharCode(v)
  })
}

/**
 * 进程快照
 * @returns 
 */
export function ProcessSnapshot(): processInfo[] | false {
  //test:ok
  return api.ProcessSnapshot();
}


interface PS_CB {
  (p: processInfo): void;
}
/**
 * 进程快照 回调形式
 * @returns 
 */
export function ProcessSnapshot_cb(callback: PS_CB) {
  //test:ok
  return api.ProcessSnapshot_cb(callback);
}

export interface EnumProcessesCallback {
  (processId: number): any;
}
/**
 * 提供了进程快照和基于快照的进程树，内部做了一个完整的循环。
 * 如果要对ProcessId进程处理或操作。建议使用EnumProcesses，因为只做了一次循环。
 * 回调传回Id可以对Id做更多操作。但快照有个好处,没有权限方面限制。
 * @function 枚举进程,Psapi.dll->EnumProcesses
 * @param callback EnumProcessCallback:(processId:number):any
 * @returns 如果函数调用成功返回真
 * @returns Returns true if the function call succeeds
 */
export function EnumProcesses(callback: EnumProcessesCallback) {
  return api.EnumProcesses(callback)
}

/**
 * 取当前进程ID，但并不确定用在electron上是什么效果。
 */
export function GetCurrentProcessId() {
  return api.GetCurrentProcessId()
}


//--------------------包装后方法，小写开头
/**
 * 进程ID取文件路径
 * @param ProcessId 
 * @returns 
 */
export function _filePathFromProcessId(ProcessId: number): string {
  let path = QueryFullProcessImageName(ProcessId) as string
  let drives = GetDrives()
  for (let i = 0; i < drives.length; i++) {
    let drive = drives[i]
    let _dos = DriveToDosDevice(drive)
    if (path.includes(_dos)) {
      return path.replace(_dos, drive + ':')
    }
  }
  return ''
}


/**
 * 生成进程树
 * @returns 
 */
export function _processTree() {
  let temp = {} as any, tree = {} as any;
  ProcessSnapshot_cb((p) => {
    temp[p.Id] = p
  })
  for (let i in temp) {
    if (temp[i].ParentId && temp[temp[i].ParentId]) {
      if (!temp[temp[i].ParentId].children) {
        temp[temp[i].ParentId].children = new Object();
      }
      temp[temp[i].ParentId].children[temp[i].Id] = temp[i];
    } else {
      tree[temp[i].Id] = temp[i];
    }
  }
  temp = null;
  return tree;
}
