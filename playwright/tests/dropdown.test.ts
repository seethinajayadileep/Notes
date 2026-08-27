import {expect,test} from "@playwright/test"
test("handling drop down",async({page})=>{
await page.goto("https://www.testmuai.com/selenium-playground/select-dropdown-demo/")
await page.selectOption("#select-demo",{
    //label:"Tuesday"
    index:4
})
await page.waitForTimeout(1000)
await page.selectOption("#multi-select",[{
    label:"Texas"
},
{
    index:2
}])
await page.waitForTimeout(3000)
})
test("bootstrap dropdown",async({page})=>{
    await page.goto("https://www.testmuai.com/selenium-playground/jquery-dropdown-search-demo/")
    await page.click("#country+span")
    await page.locator("ul#select2-country-results").locator("li",{
            hasText:"India"
        }).click()
    await page.waitForTimeout(3000)
})