import {expect,test} from "@playwright/test"
import RegisterPage from "../pages/signupPage";
import LoginPage from "../pages/loginpage";
import HomePage from "../pages/homepage";
import * as data from "../test-data/addToCart-test-data.json"

 test("signup page",async({page,baseURL})=>{
    await page.goto(baseURL+"index.php?route=account/register")
    const signupPage=new RegisterPage(page)
   await signupPage.enterFirstName(data.firstname)
    await signupPage.enterLastName(data.lastname)
     await signupPage.enterPassword(data.password)
       await signupPage.enterPhoneNumber(data.phonenumber)
    await signupPage.confirmPassword(data.password)
    await signupPage.enterEmail(data.email)
     await signupPage.clickTermAndConditions()

    await signupPage.clickContinueToRegister()


 })

test("login page",async({page,baseURL})=>{
    await page.goto(baseURL+"index.php?route=account/login")
     const loginPage=new LoginPage(page)
     await loginPage.enterEmail(data.email)
     await loginPage.enterPassword(data.password)
     await loginPage.clickLogin();
})
test("ordering",async({page,baseURL})=>{
  await page.goto(baseURL+"index.php?route=common/home")
    const homePage=new HomePage(page)

   
    await homePage.ClickLaptopSection()
    await page.waitForLoadState('networkidle');
    await homePage.SelectProduct()
    await page.waitForLoadState('networkidle');
    await homePage.Order()
    
})