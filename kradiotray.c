/* You compile the app with the following command
 * gcc -Wall -g kradiotray.c -o kradiotray `pkg-config --cflags --libs gtk+-2.0`
 * Then launch it ./kradiotray
 */

#include <gtk/gtk.h>

GtkWidget *menu, *play_item, *mute_item, *stop_item, *voldown_item, *volup_item;

void play (GtkWidget *tray_icon,
             gpointer userdata)
{
    g_spawn_command_line_async("konzolno-radio pause", NULL);
}

void stop (GtkWidget *tray_icon,
           gpointer userdata)
{
    g_spawn_command_line_async("konzolno-radio stop", NULL);
}

void voldown (GtkWidget *tray_icon,
               gpointer userdata)
{
    g_spawn_command_line_async("konzolno-radio voldown", NULL);
}

void volup (GtkWidget *tray_icon,
             gpointer userdata)
{
    g_spawn_command_line_async("konzolno-radio volup", NULL);
}

void mute (GtkWidget *tray_icon,
           gpointer userdata)
{
    g_spawn_command_line_async("konzolno-radio mute", NULL);
}

/* This assumes that button is a Button widget.
 * Now, when the mouse is over the button and a mouse button is pressed,
 * the function cb_button_click() will be called.
 */
static gboolean cb_button_click(GtkStatusIcon *tray_icon,
                                GdkEventButton *ev,
                                gpointer userdata)
{
  switch (ev->button) {
    case 1:
       gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL, ev->button, ev->time);
       break;
    case 3:
       gtk_main_quit();
       break;
  }

  return FALSE;

}

static void setup() {
  GtkStatusIcon *tray_icon;

  tray_icon = gtk_status_icon_new_from_file("/usr/share/icons/gnome/24x24/mimetypes/audio-x-generic.png");
  g_signal_connect(tray_icon,"button-press-event",
                   G_CALLBACK(cb_button_click), NULL);

  menu = gtk_menu_new();

  /* Create the menu items */
  play_item  = gtk_image_menu_item_new_with_label("Play/Pause");
  stop_item  = gtk_image_menu_item_new_with_label("Stop");
  voldown_item = gtk_image_menu_item_new_with_label("Voldown");
  volup_item = gtk_image_menu_item_new_with_label("Volup");
  mute_item = gtk_image_menu_item_new_with_label("Mute");

  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(play_item),
                                gtk_image_new_from_stock(GTK_STOCK_MEDIA_PLAY, GTK_ICON_SIZE_MENU));
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(stop_item),
                                gtk_image_new_from_stock(GTK_STOCK_MEDIA_STOP, GTK_ICON_SIZE_MENU));
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(voldown_item),
                                gtk_image_new_from_file("/usr/share/icons/gnome/24x24/status/audio-volume-low.png")); // GTK_ICON_SIZE_MENU));
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(volup_item),
                                gtk_image_new_from_file("/usr/share/icons/gnome/24x24/status/audio-volume-medium.png")); //GTK_ICON_SIZE_MENU));
  gtk_image_menu_item_set_image(GTK_IMAGE_MENU_ITEM(mute_item),
                                gtk_image_new_from_file("/usr/share/icons/gnome/24x24/status/audio-volume-muted.png"));// GTK_ICON_SIZE_MENU));

  /* Registration of callbacks */
  g_signal_connect(play_item, "activate",
                   (GCallback) play, tray_icon);
  g_signal_connect(stop_item, "activate",
                   (GCallback) stop, tray_icon);
  g_signal_connect(voldown_item, "activate",
                   (GCallback) voldown, tray_icon);
  g_signal_connect(volup_item, "activate",
                   (GCallback) volup, tray_icon);
  g_signal_connect(mute_item, "activate",
                   (GCallback) mute, tray_icon);

  /* Add them to the menu */
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), play_item);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), stop_item);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), voldown_item);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), volup_item);
  gtk_menu_shell_append(GTK_MENU_SHELL(menu), mute_item);

  /* We do need to show all menu items */
  gtk_widget_show_all(menu);

};

int main(gint argc, gchar **argv) {
    gtk_init(&argc, &argv);
    setup();
    gtk_main();

    return 0;
}
