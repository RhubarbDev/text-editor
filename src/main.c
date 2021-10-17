#include <gtk/gtk.h>
#include "save.h"
#include <stdio.h>

void css_set(GtkCssProvider * provider, GtkWidget *g_widget);

typedef enum { false, true } bool;

GtkWidget	*textview;
GtkWidget	*saveopen_button;
GtkWidget	*file_label;
GtkWidget	*opendialog;
GtkWidget	*savedialog;

int main(int argc, char *argv[])
{
    GtkWidget       *window; 
    GtkBuilder      *builder;
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");
    
    textview = GTK_WIDGET(gtk_builder_get_object(builder, "text_space"));
    saveopen_button = GTK_WIDGET(gtk_builder_get_object(builder, "saveopen_button"));
    file_label = GTK_WIDGET(gtk_builder_get_object(builder, "file_label"));
        
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));  
    gtk_builder_connect_signals(builder, NULL);
    
    gtk_button_set_label(saveopen_button, "Open");
       
    GtkCssProvider *provider = gtk_css_provider_new ();
    gtk_css_provider_load_from_path(provider, "glade/theme.css", NULL);
   
    css_set(provider, textview);
    
    opendialog = gtk_file_chooser_dialog_new ("Open File", window, GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    savedialog = gtk_file_chooser_dialog_new ("Save File", window, GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
    
    gtk_widget_show(window); 
    g_object_unref(builder);
            
    gtk_main();
    return 0;
}

// called when window is closed
void on_window_main_destroy()
{
    // save file here <---
    gtk_main_quit();
}

bool file = false; // if text file empty 

void on_textbuffer_changed()
{
    if (!file) { gtk_button_set_label(saveopen_button, "Save"); file = true; }
    // scan text and syntax highlight
}

void open_file_helper(char *path)
{
    printf(path); // placeholder
}

void save_file_helper(char *path)
{
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);
    char *text;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    save_file(text, path);
    gtk_label_set_text(file_label, path);
}

bool hasfile = false;

void on_saveopen_button_clicked()
{
    char *label = gtk_button_get_label(saveopen_button);
    if (strcmp(label, "Open") == 0){
    	if (gtk_dialog_run (GTK_DIALOG (opendialog)) == GTK_RESPONSE_ACCEPT)
    	{
    	    char *filepath;
    	    filepath = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (opendialog));
    	    open_file_helper(filepath);
    	    g_free(filepath);
    	}
    	gtk_widget_destroy(opendialog);
    }
    
    if (strcmp(label, "Save") == 0){
    	if (hasfile){
    	    save_file_helper(gtk_label_get_text(file_label));
    	}
        else if (gtk_dialog_run (GTK_DIALOG (savedialog)) == GTK_RESPONSE_ACCEPT)
        {
            char *filepath;
            filepath = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (savedialog));
            save_file_helper(filepath);
            g_free(filepath);
            gtk_widget_destroy(savedialog);
            hasfile = true;
        }
    }
}

void css_set(GtkCssProvider * cssProvider, GtkWidget *g_widget)
{
    GtkStyleContext *context = gtk_widget_get_style_context(g_widget);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(cssProvider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

