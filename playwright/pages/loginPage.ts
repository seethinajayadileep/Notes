import {Page} from "@playwright/test"
export default class LoginPage{
    constructor(public page:Page){


    }
    async loginpage(email:string,password:string){
        this.enterEmail(email)
        this.enterPassword(password)
        this.clickLogin()
    }
    async enterEmail(email:string){
        await this.page.locator("input[name='email']").fill(email)
    }
    async enterPassword(password:string){
        await this.page.locator("input[name='password']").fill(password)
    }
    async clickLogin(){
        await this.page.locator("input[type='submit']").click();
    }
}