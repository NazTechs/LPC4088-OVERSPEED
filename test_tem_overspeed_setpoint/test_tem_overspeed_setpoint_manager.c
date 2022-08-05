
void  test_tem_overspeed_setpoint_manager(uint8_t key, uint8_t *MenuState, uint8_t *MenuRender)
{																		

				if (key == 65 )
				{
					
					Menu_State = TEST_MENU;
					RENDER_REQ(Menu_Render,REDRAW);

				}

				
				
				if (key == 19 ) {
					RENDER_REQ(*MenuRender, REDRAW);
					*MenuState = TEST_MENU;

				}								
}