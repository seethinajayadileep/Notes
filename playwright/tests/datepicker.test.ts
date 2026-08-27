import {test,expect} from "@playwright/test"
test("calendar demo filling",async({page})=>{
   await page.goto("https://www.testmuai.com/selenium-playground/bootstrap-date-picker-demo/")
 await page.locator("input[placeholder='Start date']").fill("2000-12-12")
 await page.waitForTimeout(3000)


})