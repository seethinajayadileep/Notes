import {Page} from "@playwright/test"
export default class HomePage{
    constructor(public page:Page){

    }
    
  async ClickLaptopSection(){
    await this.page.locator('h4:has-text("Laptops")').click();

  }
async SelectProduct() {
  await this.page.getByRole('link', { name: 'Palm Treo Pro', exact: true }).click();
}
  async Order(){
    await this.page.getByRole('button', { name: 'Buy now' }).click();
  }
}