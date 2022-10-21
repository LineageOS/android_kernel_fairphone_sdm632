#include <linux/fs.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/setup.h>

static char new_command_line[COMMAND_LINE_SIZE];

static int cmdline_proc_show(struct seq_file *m, void *v)
{
	seq_printf(m, "%s\n", new_command_line);
	return 0;
}

static int cmdline_proc_open(struct inode *inode, struct file *file)
{
	return single_open(file, cmdline_proc_show, NULL);
}

static const struct file_operations cmdline_proc_fops = {
	.open		= cmdline_proc_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

#define DYN_PART_CMDLINE_FIND "skip_initramfs"
#define DYN_PART_CMDLINE_REPLACE "androidboot.force_normal_boot=1"

static int __init proc_cmdline_init(void)
{
	size_t tail_len;
	char *offset_addr;
	char *cmd = new_command_line;

	strcpy(cmd, saved_command_line);

	// Find offset of find string
	offset_addr = strstr(cmd, DYN_PART_CMDLINE_FIND);
	if (offset_addr) {
		tail_len = strlen(offset_addr + strlen(DYN_PART_CMDLINE_FIND));

		// Move tail back so we have space for replace string
		memmove(offset_addr + strlen(DYN_PART_CMDLINE_REPLACE),
				offset_addr + strlen(DYN_PART_CMDLINE_FIND),
				tail_len + 1);
		// Copy replacement into the newly empty space
		memcpy(offset_addr, DYN_PART_CMDLINE_REPLACE, strlen(DYN_PART_CMDLINE_REPLACE));
	}

	proc_create("cmdline", 0, NULL, &cmdline_proc_fops);
	return 0;
}
fs_initcall(proc_cmdline_init);
