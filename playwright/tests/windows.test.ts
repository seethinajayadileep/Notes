import {expect,test} from "@playwright/test"
test("window",async({page})=>{
  await  page.goto("https://www.testmuai.com/selenium-playground/window-popup-modal-demo/")
  console.log(page.url())
//   const [newwindow]=await Promise.all([
//     page.waitForEvent("popup"),
//     page.click("//*[@id='__next']/div/main/section[2]/div/div[1]/div/div[1]/a")
//   ])
 const [multiwindow]=await Promise.all([
    page.waitForEvent("popup"),
    page.click("//a[@title='Follow Twitter & Facebook']")
 ])
 const pages=multiwindow.context().pages()
 console.log(pages.length)
 pages.forEach(singlepage=>{
console.log(singlepage.url())
 })
  console.log(multiwindow.url())
})