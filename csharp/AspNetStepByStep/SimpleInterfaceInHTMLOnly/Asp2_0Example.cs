
using System.Web;
public partial class Asp2_0Example : System.Web.UI.Page
{
	public void ShowLineage()
	{
		Response.Write("Check out the family tree: <br> <br>");
		Response.Write(this.GetType().ToString());
		Response.Write(" which derives from <br> ");
		Response.Write(this.GetType().BaseType.ToString());
		Response.Write(" which derives from <br> ");
		Response.Write(this.GetType().BaseType.BaseType.ToString());
		Response.Write(" which derives from <br> ");
		Response.Write(this.GetType().BaseType.BaseType.BaseType.ToString());
		Response.Write(" which derives from <br> ");
		Response.Write(this.GetType().BaseType.BaseType.BaseType.BaseType.ToString());
	}
}