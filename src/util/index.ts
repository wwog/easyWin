/**
 * 生成树状结构数组
 * @param list 
 * @param id 
 * @param pid 
 * @returns 
 */
export function buildArrTree(list: any, id = 'id', pid = 'pid') {
  let temp = {} as any, tree = [];
  for (let i in list) {
    temp[list[i][id]] = list[i];
  }
  for (let i in temp) {
    if (temp[i][pid] && temp[temp[i][pid]]) {
      if (!temp[temp[i][pid]].children) {
        temp[temp[i][pid]].children = [];
      }
      temp[temp[i][pid]].children.push(temp[i]);
    } else {
      tree.push(temp[i]);
    }
  }
  return tree;
}
/**
 * 生成树状结构对象
 * @param list 
 * @param id 
 * @param pid 
 * @returns 
 */
export function buildObjTree(list:any, id = 'id', pid = 'pid') {
  let temp = {} as any, tree = {} as any;
  for (let i in list) {
    temp[list[i][id]] = list[i];
  }
  for (let i in temp) {
    if (temp[i][pid] && temp[temp[i][pid]]) {
      if (!temp[temp[i][pid]].children) {
        temp[temp[i][pid]].children = new Object();
      }
      temp[temp[i][pid]].children[temp[i][id]] = temp[i];
    } else {
      tree[temp[i][id]] = temp[i];
    }
  }
  return tree;
}
