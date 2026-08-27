import {test as mytest } from "@playwright/test"
type jaya={
age:number,
email:string

}
const myfixtureTest=mytest.extend<jaya>({
    age:27,
    email:"jaya1@gmail.com"
})
export const test=myfixtureTest