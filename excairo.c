#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
 
 #define M_PI 3.14159265358979323846
int avance;
 
gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer user_data)
{
    cairo_move_to (cr, 50, 50);
    cairo_line_to (cr, 200, 50);
 
    cairo_move_to (cr, 50, 100);
    cairo_line_to (cr, 250, 100);
    cairo_rel_line_to (cr, 0, -60);
 
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width (cr, 7);
    cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_ROUND);
    cairo_stroke (cr);
 
    /*if (avance<1) return FALSE;
 
    cairo_move_to (cr, 300, 50);
    cairo_line_to (cr, 300, 150);
    cairo_line_to (cr, 100, 150);
 
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_width (cr, 7);
    cairo_set_line_cap (cr, CAIRO_LINE_CAP_SQUARE);
    cairo_set_line_join (cr, CAIRO_LINE_JOIN_MITER);
    cairo_stroke (cr);
 
    if (avance<2) return FALSE;
 
    cairo_rectangle (cr, 100, 200, 100, 100);
    cairo_set_source_rgb (cr, 0, 0, 1);
    cairo_fill(cr);
    cairo_stroke (cr);
 
    if (avance<3) return FALSE;
 
    cairo_rectangle (cr, 220, 200, 100, 50);
    cairo_set_line_width (cr, 3);
    cairo_set_source_rgb (cr, 0, 0.6, 0);
    cairo_stroke (cr);
 
    if (avance<4) return FALSE;
 
    cairo_rectangle (cr, 220, 270, 100, 50);
    cairo_set_line_width (cr, 3);
    cairo_set_source_rgb (cr, 0, 0, 1);
    cairo_fill_preserve (cr);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_stroke (cr);
 
    if (avance<5) return FALSE;
 
    cairo_arc (cr, 100, 300, 10, 0, 2*M_PI);
    cairo_set_source_rgb (cr, 0.7, 0, 0.7);
    cairo_fill(cr);
    cairo_stroke (cr);*/
 
 
    return FALSE;
}
 
 
gboolean mouse_cb(GtkWidget *widget, GdkEventButton *event, gpointer user_data)
{
    printf("clicked: bouton: %d  pos: %lf , %lf \n", event->button, event->x,event->y);
    return TRUE;
}
 
 
gboolean key_cb(GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
    if (event->keyval == GDK_KEY_Escape)
        gtk_main_quit();
 
    if (event->keyval == GDK_KEY_space)
        avance = 101;
    else
    {
        avance = (avance+1)%6;
        gtk_widget_queue_draw(widget);
    }
 
    return TRUE;
}
 
 
gboolean timeout_cb (gpointer data)
{
    if (avance >100)
        return FALSE;
 
    avance = (avance+1)%6;
    gtk_widget_queue_draw((GtkWidget*)data);
 
    return TRUE;
}
 
 
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
 
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(window), darea);
 
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(draw_cb), NULL); 
    g_signal_connect(window, "button-press-event", G_CALLBACK(mouse_cb), NULL);
    g_signal_connect(window, "key-press-event", G_CALLBACK(key_cb), NULL);
 
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400); 
    gtk_window_set_title(GTK_WINDOW(window), "Lines");
    gtk_widget_show_all(window);
 
    avance=0;    
 
    g_timeout_add(250, (GSourceFunc)timeout_cb, window);
 
    gtk_main();
 
    return 0;
}