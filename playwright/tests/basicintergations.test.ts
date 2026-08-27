import {expect,test} from "@playwright/test"
// test("",async({page})=>{
//     await page.goto("https://www.testmuai.com/selenium-playground/simple-form-demo/")
//     const messageInput=page.locator("input#user-message")
//     console.log(await messageInput.getAttribute("placeholder"))
//     expect(messageInput).toHaveAttribute("placeholder","Please enter your Message")
//     await messageInput.fill("hi");
//     await  page.waitForTimeout(5000)
//      console.log("after enter data"+await messageInput.inputValue())

// })

// test("checkbox",async({page})=>{
//     await page.goto("https://www.testmuai.com/selenium-playground/checkbox-demo/")
//  const  singleCheckbox=  page.locator("//*[@id='__next']/div/main/div/section/div/div/div[1]/label/input")
// expect(singleCheckbox).not.toBeChecked()
// await singleCheckbox.check();
// await page.waitForTimeout(5000)
// })
