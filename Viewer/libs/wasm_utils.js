export function vectorIntToArray(v) {
    let res = [];
    console.log("v.size(): ", v.size());
    for (let i = 0; i < v.size(); ++i) {
        res.push(v.get(i));
    }
    return res;
}

export function arrayToVectorInt(v, module) {
    let res = new module.VectorInt();
    for (let x of v) res.push_back(x);
    return res; 
}