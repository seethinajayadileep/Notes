import {Page} from "@playwright/test"
export default class RegisterPage{
    constructor(public page:Page){


    }
   async enterFirstName(firstname:string){
    await this.page.locator("input[name='firstname']").fill(firstname)

    }
      async enterLastName(lastname:string){
    await this.page.locator("input[name='lastname']").fill(lastname)

    }
      async enterEmail(email:string){
    await this.page.locator("input[name='email']").fill(email)

    }
      async enterPhoneNumber(phonenumber:string){
    await this.page.locator("input[name='telephone']").fill(phonenumber)

    }
      async enterPassword(password:string){
        await this.page.locator("input[name='password']").fill(password)
    

    }
     async confirmPassword(password:string){
       
    await this.page.locator("input[name='confirm']").fill(password)

    }
    async isSubcribeChecked(){
       return await this.page.locator("#input-newsletter-no").isChecked();
    }
    async clickTermAndConditions(){
       const inputAgree=  this.page.locator("//*[@id='input-agree']")
       await inputAgree.check({ force: true });

    }

    async clickContinueToRegister(){
        await this.page.click("input[type='submit']");

    }
}